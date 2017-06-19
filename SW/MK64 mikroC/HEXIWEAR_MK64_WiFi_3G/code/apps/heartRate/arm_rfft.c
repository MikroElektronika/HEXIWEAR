// File: arm_rfft.c

// Definiions of functionalities in ARM RFFT module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "arm_rfft.h"
#include "arm_common_tables.h"

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

void arm_bitreversal_32( uint32_t * pSrc,
    const uint16_t bitRevLen, const uint16_t* pBitRevTable )
{
    asm {
        ADDS     R3,R1,#1
        CMP      R3,#1
        IT       LS
        BXLS     LR
        STMDB SP!, (R4-R9)
        ADDS     R1,R2,#2
        LSRS     R3,R3,#2
arm_bitreversal_32_0: // loop unrolled by 2
        LDRH     R8,[R1,#4]
        LDRH     R9,[R1,#2]
        LDRH     R2,[R1,#0]
        LDRH     R12,[R1,#-2]
        ADD      R8,R0,R8
        ADD      R9,R0,R9
        ADD      R2,R0,R2
        ADD      R12,R0,R12
        LDR      R7,[R9,#0]
        LDR      R6,[R8,#0]
        LDR      R5,[R2,#0]
        LDR      R4,[R12,#0]
        STR      R6,[R9,#0]
        STR      R7,[R8,#0]
        STR      R5,[R12,#0]
        STR      R4,[R2,#0]
        LDR      R7,[R9,#4]
        LDR      R6,[R8,#4]
        LDR      R5,[R2,#4]
        LDR      R4,[R12,#4]
        STR      R6,[R9,#4]
        STR      R7,[R8,#4]
        STR      R5,[R12,#4]
        STR      R4,[R2,#4]
        ADDS     R1,R1,#8
        SUBS     R3,R3,#1
        BNE      arm_bitreversal_32_0
        LDM SP!, (R4-R9)
        // BX       lr
    }
}

// Prepares data for inverse cfft
static void merge_rfft_f32(
    arm_rfft_fast_instance_f32* pS, double* p, double* pOut )
{
    uint32_t  k;                       // Loop Counter
    double twR, twI;                   // RFFT Twiddle coefficients
    double *pCoeff = pS->pTwiddleRFFT; // Points to RFFT Twiddle factors
    double *pA = p;                    // increasing pointer
    double *pB = p;                    // decreasing pointer
    double xAR, xAI, xBR, xBI;         // temporary variables
    double t1a, t1b, r, s, t, u;       // temporary variables

    k = ( pS->Sint ).fftLen - 1;

    xAR = pA[0];
    xAI = pA[1];

    pCoeff += 2 ;

    *pOut++ = 0.5f * ( xAR + xAI );
    *pOut++ = 0.5f * ( xAR - xAI );

    pB = p + 2 * k ;
    pA += 2;

    while( k > 0u )
    {
        // G is half of the frequency complex spectrum
        //for k = 2:N
        // Xk(k) = 
        //     1/2 * (G(k) + conj(G(N-k+2)) + Tw(k)*( G(k) - conj(G(N-k+2))));
        xBI = pB[1];
        xBR = pB[0];
        xAR = pA[0];
        xAI = pA[1];

        twR = *pCoeff++;
        twI = *pCoeff++;

        t1a = xAR - xBR ;
        t1b = xAI + xBI ;

        r = twR * t1a;
        s = twI * t1b;
        t = twI * t1a;
        u = twR * t1b;

        // real(tw * (xA - xB)) = twR * (xAR - xBR) - twI * (xAI - xBI);
        // imag(tw * (xA - xB)) = twI * (xAR - xBR) + twR * (xAI - xBI);
        *pOut++ = 0.5f * ( xAR + xBR - r - s ); //xAR
        *pOut++ = 0.5f * ( xAI - xBI + t - u ); //xAI

        pA += 2;
        pB -= 2;
        k--;
    }
}

static void stage_rfft_f32(
    arm_rfft_fast_instance_f32* S, double* p, double* pOut )
{
    uint32_t  k;                      // Loop Counter
    double twR, twI;                  // RFFT Twiddle coefficients
    double* pCoeff = S->pTwiddleRFFT; // Points to RFFT Twiddle factors
    double* pA = p;                   // increasing pointer
    double* pB = p;                   // decreasing pointer
    double xAR, xAI, xBR, xBI;        // temporary variables
    double t1a, t1b;                  // temporary variables
    double p0, p1, p2, p3;            // temporary variables

    k = ( S->Sint ).fftLen - 1;
    
    // Pack first and last sample of the frequency domain together

    xBR = pB[0];
    xBI = pB[1];
    xAR = pA[0];
    xAI = pA[1];

    twR = *pCoeff++;
    twI = *pCoeff++;

    // U1 = XA(1) + XB(1); % It is real
    t1a = xBR + xAR  ;

    // U2 = XB(1) - XA(1); % It is imaginary
    t1b = xBI + xAI  ;

    // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
    // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
    *pOut++ = 0.5f * ( t1a + t1b );
    *pOut++ = 0.5f * ( t1a - t1b );

    // XA(1) = 1/2*( U1 - imag(U2) +  i*( U1 +imag(U2) ));
    pB = p + 2 * k;
    pA += 2;

    do
    {
        // function X = my_split_rfft(X, ifftFlag)
        // % X is a series of real numbers
        // L  = length(X);
        // XC = X(1:2:end) +i*X(2:2:end);
        // XA = fft(XC);
        // XB = conj(XA([1 end:-1:2]));
        // TW = i*exp(-2*pi*i*[0:L/2-1]/L).';
        // for l = 2:L/2
        //    XA(l) = 1/2 * (XA(l) + XB(l) + TW(l) * (XB(l) - XA(l)));
        // end
        // XA(1) = 1/2* (XA(1) + XB(1) + TW(1) * (XB(1) - XA(1))) +
        //     i*( 1/2*( XA(1) + XB(1) + i*( XA(1) - XB(1))));
        // X = XA;

        xBI = pB[1];
        xBR = pB[0];
        xAR = pA[0];
        xAI = pA[1];

        twR = *pCoeff++;
        twI = *pCoeff++;

        t1a = xBR - xAR ;
        t1b = xBI + xAI ;

        // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
        // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
        p0 = twR * t1a;
        p1 = twI * t1a;
        p2 = twR * t1b;
        p3 = twI * t1b;

        *pOut++ = 0.5f * ( xAR + xBR + p0 + p3 ); //xAR
        *pOut++ = 0.5f * ( xAI - xBI + p1 - p2 ); //xAI

        pA += 2;
        pB -= 2;
        k--;
    } while( k > 0u );
}

static void arm_radix8_butterfly_f32( double* pSrc, uint16_t fftLen,
    const double* pCoef, uint16_t twidCoefModifier )
{
    uint32_t ia1, ia2, ia3, ia4, ia5, ia6, ia7;
    uint32_t i1, i2, i3, i4, i5, i6, i7, i8;
    uint32_t id;
    uint32_t n1, n2, j;

    double r1, r2, r3, r4, r5, r6, r7, r8;
    double t1, t2;
    double s1, s2, s3, s4, s5, s6, s7, s8;
    double p1, p2, p3, p4;
    double co2, co3, co4, co5, co6, co7, co8;
    double si2, si3, si4, si5, si6, si7, si8;
    const double C81 = 0.70710678118f;

    n2 = fftLen;

    do
    {
        n1 = n2;
        n2 = n2 >> 3;
        i1 = 0;

        do
        {
            i2 = i1 + n2;
            i3 = i2 + n2;
            i4 = i3 + n2;
            i5 = i4 + n2;
            i6 = i5 + n2;
            i7 = i6 + n2;
            i8 = i7 + n2;
            r1 = pSrc[2 * i1] + pSrc[2 * i5];
            r5 = pSrc[2 * i1] - pSrc[2 * i5];
            r2 = pSrc[2 * i2] + pSrc[2 * i6];
            r6 = pSrc[2 * i2] - pSrc[2 * i6];
            r3 = pSrc[2 * i3] + pSrc[2 * i7];
            r7 = pSrc[2 * i3] - pSrc[2 * i7];
            r4 = pSrc[2 * i4] + pSrc[2 * i8];
            r8 = pSrc[2 * i4] - pSrc[2 * i8];
            t1 = r1 - r3;
            r1 = r1 + r3;
            r3 = r2 - r4;
            r2 = r2 + r4;
            pSrc[2 * i1] = r1 + r2;
            pSrc[2 * i5] = r1 - r2;
            r1 = pSrc[2 * i1 + 1] + pSrc[2 * i5 + 1];
            s5 = pSrc[2 * i1 + 1] - pSrc[2 * i5 + 1];
            r2 = pSrc[2 * i2 + 1] + pSrc[2 * i6 + 1];
            s6 = pSrc[2 * i2 + 1] - pSrc[2 * i6 + 1];
            s3 = pSrc[2 * i3 + 1] + pSrc[2 * i7 + 1];
            s7 = pSrc[2 * i3 + 1] - pSrc[2 * i7 + 1];
            r4 = pSrc[2 * i4 + 1] + pSrc[2 * i8 + 1];
            s8 = pSrc[2 * i4 + 1] - pSrc[2 * i8 + 1];
            t2 = r1 - s3;
            r1 = r1 + s3;
            s3 = r2 - r4;
            r2 = r2 + r4;
            pSrc[2 * i1 + 1] = r1 + r2;
            pSrc[2 * i5 + 1] = r1 - r2;
            pSrc[2 * i3]     = t1 + s3;
            pSrc[2 * i7]     = t1 - s3;
            pSrc[2 * i3 + 1] = t2 - r3;
            pSrc[2 * i7 + 1] = t2 + r3;
            r1 = (r6 - r8) * C81;
            r6 = (r6 + r8) * C81;
            r2 = (s6 - s8) * C81;
            s6 = (s6 + s8) * C81;
            t1 = r5 - r1;
            r5 = r5 + r1;
            r8 = r7 - r6;
            r7 = r7 + r6;
            t2 = s5 - r2;
            s5 = s5 + r2;
            s8 = s7 - s6;
            s7 = s7 + s6;
            pSrc[2 * i2]     = r5 + s7;
            pSrc[2 * i8]     = r5 - s7;
            pSrc[2 * i6]     = t1 + s8;
            pSrc[2 * i4]     = t1 - s8;
            pSrc[2 * i2 + 1] = s5 - r7;
            pSrc[2 * i8 + 1] = s5 + r7;
            pSrc[2 * i6 + 1] = t2 - r8;
            pSrc[2 * i4 + 1] = t2 + r8;

            i1 += n1;
        } while( i1 < fftLen );

        if( n2 < 8 )
            break;

        ia1 = 0;
        j = 1;

        do
        {
            // index calculation for the coefficients
            id  = ia1 + twidCoefModifier;
            ia1 = id;
            ia2 = ia1 + id;
            ia3 = ia2 + id;
            ia4 = ia3 + id;
            ia5 = ia4 + id;
            ia6 = ia5 + id;
            ia7 = ia6 + id;

            co2 = pCoef[2 * ia1];
            co3 = pCoef[2 * ia2];
            co4 = pCoef[2 * ia3];
            co5 = pCoef[2 * ia4];
            co6 = pCoef[2 * ia5];
            co7 = pCoef[2 * ia6];
            co8 = pCoef[2 * ia7];
            si2 = pCoef[2 * ia1 + 1];
            si3 = pCoef[2 * ia2 + 1];
            si4 = pCoef[2 * ia3 + 1];
            si5 = pCoef[2 * ia4 + 1];
            si6 = pCoef[2 * ia5 + 1];
            si7 = pCoef[2 * ia6 + 1];
            si8 = pCoef[2 * ia7 + 1];

            i1 = j;

            do
            {
                // index calculation for the input
                i2 = i1 + n2;
                i3 = i2 + n2;
                i4 = i3 + n2;
                i5 = i4 + n2;
                i6 = i5 + n2;
                i7 = i6 + n2;
                i8 = i7 + n2;
                r1 = pSrc[2 * i1] + pSrc[2 * i5];
                r5 = pSrc[2 * i1] - pSrc[2 * i5];
                r2 = pSrc[2 * i2] + pSrc[2 * i6];
                r6 = pSrc[2 * i2] - pSrc[2 * i6];
                r3 = pSrc[2 * i3] + pSrc[2 * i7];
                r7 = pSrc[2 * i3] - pSrc[2 * i7];
                r4 = pSrc[2 * i4] + pSrc[2 * i8];
                r8 = pSrc[2 * i4] - pSrc[2 * i8];
                t1 = r1 - r3;
                r1 = r1 + r3;
                r3 = r2 - r4;
                r2 = r2 + r4;
                pSrc[2 * i1] = r1 + r2;
                r2 = r1 - r2;
                s1 = pSrc[2 * i1 + 1] + pSrc[2 * i5 + 1];
                s5 = pSrc[2 * i1 + 1] - pSrc[2 * i5 + 1];
                s2 = pSrc[2 * i2 + 1] + pSrc[2 * i6 + 1];
                s6 = pSrc[2 * i2 + 1] - pSrc[2 * i6 + 1];
                s3 = pSrc[2 * i3 + 1] + pSrc[2 * i7 + 1];
                s7 = pSrc[2 * i3 + 1] - pSrc[2 * i7 + 1];
                s4 = pSrc[2 * i4 + 1] + pSrc[2 * i8 + 1];
                s8 = pSrc[2 * i4 + 1] - pSrc[2 * i8 + 1];
                t2 = s1 - s3;
                s1 = s1 + s3;
                s3 = s2 - s4;
                s2 = s2 + s4;
                r1 = t1 + s3;
                t1 = t1 - s3;
                pSrc[2 * i1 + 1] = s1 + s2;
                s2 = s1 - s2;
                s1 = t2 - r3;
                t2 = t2 + r3;
                p1 = co5 * r2;
                p2 = si5 * s2;
                p3 = co5 * s2;
                p4 = si5 * r2;
                pSrc[2 * i5]     = p1 + p2;
                pSrc[2 * i5 + 1] = p3 - p4;
                p1 = co3 * r1;
                p2 = si3 * s1;
                p3 = co3 * s1;
                p4 = si3 * r1;
                pSrc[2 * i3]     = p1 + p2;
                pSrc[2 * i3 + 1] = p3 - p4;
                p1 = co7 * t1;
                p2 = si7 * t2;
                p3 = co7 * t2;
                p4 = si7 * t1;
                pSrc[2 * i7]     = p1 + p2;
                pSrc[2 * i7 + 1] = p3 - p4;
                r1 = (r6 - r8) * C81;
                r6 = (r6 + r8) * C81;
                s1 = (s6 - s8) * C81;
                s6 = (s6 + s8) * C81;
                t1 = r5 - r1;
                r5 = r5 + r1;
                r8 = r7 - r6;
                r7 = r7 + r6;
                t2 = s5 - s1;
                s5 = s5 + s1;
                s8 = s7 - s6;
                s7 = s7 + s6;
                r1 = r5 + s7;
                r5 = r5 - s7;
                r6 = t1 + s8;
                t1 = t1 - s8;
                s1 = s5 - r7;
                s5 = s5 + r7;
                s6 = t2 - r8;
                t2 = t2 + r8;
                p1 = co2 * r1;
                p2 = si2 * s1;
                p3 = co2 * s1;
                p4 = si2 * r1;
                pSrc[2 * i2]     = p1 + p2;
                pSrc[2 * i2 + 1] = p3 - p4;
                p1 = co8 * r5;
                p2 = si8 * s5;
                p3 = co8 * s5;
                p4 = si8 * r5;
                pSrc[2 * i8]     = p1 + p2;
                pSrc[2 * i8 + 1] = p3 - p4;
                p1 = co6 * r6;
                p2 = si6 * s6;
                p3 = co6 * s6;
                p4 = si6 * r6;
                pSrc[2 * i6]     = p1 + p2;
                pSrc[2 * i6 + 1] = p3 - p4;
                p1 = co4 * t1;
                p2 = si4 * t2;
                p3 = co4 * t2;
                p4 = si4 * t1;
                pSrc[2 * i4]     = p1 + p2;
                pSrc[2 * i4 + 1] = p3 - p4;

                i1 += n1;
         } while( i1 < fftLen );

            j++;
        } while( j < n2 );

        twidCoefModifier <<= 3;
    } while( n2 > 7 );
}

static void arm_cfft_radix8by2_f32( arm_cfft_instance_f32* S, double* p1 )
{
    uint32_t L = S->fftLen;
    double *pCol1, *pCol2, *pMid1, *pMid2;
    double* p2 = p1 + L;
    const double* tw = ( double* )S->pTwiddle;
    double t1[4], t2[4], t3[4], t4[4], twR, twI;
    double m0, m1, m2, m3;
    uint32_t ll;

    pCol1 = p1;
    pCol2 = p2;

    // Define new length
    L >>= 1;
    // Initialize mid pointers
    pMid1 = p1 + L;
    pMid2 = p2 + L;

    // do two dot Fourier transform
    for( ll = L >> 2; ll > 0; ll-- )
    {
        t1[0] = p1[0];
        t1[1] = p1[1];
        t1[2] = p1[2];
        t1[3] = p1[3];

        t2[0] = p2[0];
        t2[1] = p2[1];
        t2[2] = p2[2];
        t2[3] = p2[3];

        t3[0] = pMid1[0];
        t3[1] = pMid1[1];
        t3[2] = pMid1[2];
        t3[3] = pMid1[3];

        t4[0] = pMid2[0];
        t4[1] = pMid2[1];
        t4[2] = pMid2[2];
        t4[3] = pMid2[3];

        *p1++ = t1[0] + t2[0];
        *p1++ = t1[1] + t2[1];
        *p1++ = t1[2] + t2[2];
        *p1++ = t1[3] + t2[3];    // col 1

        t2[0] = t1[0] - t2[0];
        t2[1] = t1[1] - t2[1];
        t2[2] = t1[2] - t2[2];
        t2[3] = t1[3] - t2[3];    // for col 2

        *pMid1++ = t3[0] + t4[0];
        *pMid1++ = t3[1] + t4[1];
        *pMid1++ = t3[2] + t4[2];
        *pMid1++ = t3[3] + t4[3]; // col 1

        t4[0] = t4[0] - t3[0];
        t4[1] = t4[1] - t3[1];
        t4[2] = t4[2] - t3[2];
        t4[3] = t4[3] - t3[3];    // for col 2

        twR = *tw++;
        twI = *tw++;

        // multiply by twiddle factors
        m0 = t2[0] * twR;
        m1 = t2[1] * twI;
        m2 = t2[1] * twR;
        m3 = t2[0] * twI;

        // R  =  R  *  Tr - I * Ti
        *p2++ = m0 + m1;
        // I  =  I  *  Tr + R * Ti
        *p2++ = m2 - m3;

        // use vertical symmetry
        //  0.9988 - 0.0491i <==> -0.0491 - 0.9988i
        m0 = t4[0] * twI;
        m1 = t4[1] * twR;
        m2 = t4[1] * twI;
        m3 = t4[0] * twR;

        *pMid2++ = m0 - m1;
        *pMid2++ = m2 + m3;

        twR = *tw++;
        twI = *tw++;

        m0 = t2[2] * twR;
        m1 = t2[3] * twI;
        m2 = t2[3] * twR;
        m3 = t2[2] * twI;

        *p2++ = m0 + m1;
        *p2++ = m2 - m3;

        m0 = t4[2] * twI;
        m1 = t4[3] * twR;
        m2 = t4[3] * twI;
        m3 = t4[2] * twR;

        *pMid2++ = m0 - m1;
        *pMid2++ = m2 + m3;
    }

    // first col
    arm_radix8_butterfly_f32( pCol1, L, ( double* )S->pTwiddle, 2u );
    // second col
    arm_radix8_butterfly_f32( pCol2, L, ( double* )S->pTwiddle, 2u );
}

void arm_cfft_radix8by4_f32( arm_cfft_instance_f32* S, double* p1 )
{
    uint32_t L = S->fftLen >> 1;
    double *pCol1, *pCol2, *pCol3, *pCol4, *pEnd1, *pEnd2, *pEnd3, *pEnd4;
    const double *tw2, *tw3, *tw4;
    double* p2 = p1 + L;
    double* p3 = p2 + L;
    double* p4 = p3 + L;
    double t2[4], t3[4], t4[4], twR, twI;
    double p1ap3_0, p1sp3_0, p1ap3_1, p1sp3_1;
    double m0, m1, m2, m3;
    uint32_t ll, twMod2, twMod3, twMod4;

    pCol1 = p1;         // points to real values by default
    pCol2 = p2;
    pCol3 = p3;
    pCol4 = p4;
    pEnd1 = p2 - 1;     // points to imaginary values by default
    pEnd2 = p3 - 1;
    pEnd3 = p4 - 1;
    pEnd4 = pEnd3 + L;

    tw2 = tw3 = tw4 = ( double* )S->pTwiddle;

    L >>= 1;

    // do four dot Fourier transform

    twMod2 = 2;
    twMod3 = 4;
    twMod4 = 6;

    // TOP
    p1ap3_0 = p1[0] + p3[0];
    p1sp3_0 = p1[0] - p3[0];
    p1ap3_1 = p1[1] + p3[1];
    p1sp3_1 = p1[1] - p3[1];

    // col 2
    t2[0] = p1sp3_0 + p2[1] - p4[1];
    t2[1] = p1sp3_1 - p2[0] + p4[0];
    // col 3
    t3[0] = p1ap3_0 - p2[0] - p4[0];
    t3[1] = p1ap3_1 - p2[1] - p4[1];
    // col 4
    t4[0] = p1sp3_0 - p2[1] + p4[1];
    t4[1] = p1sp3_1 + p2[0] - p4[0];
    // col 1
    *p1++ = p1ap3_0 + p2[0] + p4[0];
    *p1++ = p1ap3_1 + p2[1] + p4[1];

    // Twiddle factors are ones
    *p2++ = t2[0];
    *p2++ = t2[1];
    *p3++ = t3[0];
    *p3++ = t3[1];
    *p4++ = t4[0];
    *p4++ = t4[1];

    tw2 += twMod2;
    tw3 += twMod3;
    tw4 += twMod4;

    for( ll = ( L - 2 ) >> 1; ll > 0; ll-- )
    {
        // TOP
        p1ap3_0 = p1[0] + p3[0];
        p1sp3_0 = p1[0] - p3[0];
        p1ap3_1 = p1[1] + p3[1];
        p1sp3_1 = p1[1] - p3[1];
        // col 2
        t2[0] = p1sp3_0 + p2[1] - p4[1];
        t2[1] = p1sp3_1 - p2[0] + p4[0];
        // col 3
        t3[0] = p1ap3_0 - p2[0] - p4[0];
        t3[1] = p1ap3_1 - p2[1] - p4[1];
        // col 4
        t4[0] = p1sp3_0 - p2[1] + p4[1];
        t4[1] = p1sp3_1 + p2[0] - p4[0];
        // col 1 - top
        *p1++ = p1ap3_0 + p2[0] + p4[0];
        *p1++ = p1ap3_1 + p2[1] + p4[1];

        // BOTTOM
        p1ap3_1 = pEnd1[-1] + pEnd3[-1];
        p1sp3_1 = pEnd1[-1] - pEnd3[-1];
        p1ap3_0 = pEnd1[0] + pEnd3[0];
        p1sp3_0 = pEnd1[0] - pEnd3[0];
        // col 2
        t2[2] = pEnd2[0]  - pEnd4[0] + p1sp3_1;
        t2[3] = pEnd1[0] - pEnd3[0] - pEnd2[-1] + pEnd4[-1];
        // col 3
        t3[2] = p1ap3_1 - pEnd2[-1] - pEnd4[-1];
        t3[3] = p1ap3_0 - pEnd2[0]  - pEnd4[0];
        // col 4
        t4[2] = pEnd2[0]  - pEnd4[0]  - p1sp3_1;
        t4[3] = pEnd4[-1] - pEnd2[-1] - p1sp3_0;
        // col 1 - Bottom
        *pEnd1-- = p1ap3_0 + pEnd2[0] + pEnd4[0];
        *pEnd1-- = p1ap3_1 + pEnd2[-1] + pEnd4[-1];

        // COL 2
        // read twiddle factors
        twR = *tw2++;
        twI = *tw2++;
        // multiply by twiddle factors
        //  let    Z1 = a + i(b),   Z2 = c + i(d)
        //   =>  Z1 * Z2  =  (a*c - b*d) + i(b*c + a*d)

        // Top
        m0 = t2[0] * twR;
        m1 = t2[1] * twI;
        m2 = t2[1] * twR;
        m3 = t2[0] * twI;

        *p2++ = m0 + m1;
        *p2++ = m2 - m3;
        // use vertical symmetry col 2
        // 0.9997 - 0.0245i  <==>  0.0245 - 0.9997i
        // Bottom
        m0 = t2[3] * twI;
        m1 = t2[2] * twR;
        m2 = t2[2] * twI;
        m3 = t2[3] * twR;

        *pEnd2-- = m0 - m1;
        *pEnd2-- = m2 + m3;

        // COL 3
        twR = tw3[0];
        twI = tw3[1];
        tw3 += twMod3;
        // Top
        m0 = t3[0] * twR;
        m1 = t3[1] * twI;
        m2 = t3[1] * twR;
        m3 = t3[0] * twI;

        *p3++ = m0 + m1;
        *p3++ = m2 - m3;
        // use vertical symmetry col 3
        // 0.9988 - 0.0491i  <==>  -0.9988 - 0.0491i
        // Bottom
        m0 = -t3[3] * twR;
        m1 = t3[2] * twI;
        m2 = t3[2] * twR;
        m3 = t3[3] * twI;

        *pEnd3-- = m0 - m1;
        *pEnd3-- = m3 - m2;

        // COL 4
        twR = tw4[0];
        twI = tw4[1];
        tw4 += twMod4;
        // Top
        m0 = t4[0] * twR;
        m1 = t4[1] * twI;
        m2 = t4[1] * twR;
        m3 = t4[0] * twI;

        *p4++ = m0 + m1;
        *p4++ = m2 - m3;
        // use vertical symmetry col 4
        // 0.9973 - 0.0736i  <==>  -0.0736 + 0.9973i
        // Bottom
        m0 = t4[3] * twI;
        m1 = t4[2] * twR;
        m2 = t4[2] * twI;
        m3 = t4[3] * twR;

        *pEnd4-- = m0 - m1;
        *pEnd4-- = m2 + m3;
    }

    //MIDDLE
    // Twiddle factors are
    //  1.0000  0.7071-0.7071i  -1.0000i  -0.7071-0.7071i
    p1ap3_0 = p1[0] + p3[0];
    p1sp3_0 = p1[0] - p3[0];
    p1ap3_1 = p1[1] + p3[1];
    p1sp3_1 = p1[1] - p3[1];

    // col 2
    t2[0] = p1sp3_0 + p2[1] - p4[1];
    t2[1] = p1sp3_1 - p2[0] + p4[0];
    // col 3
    t3[0] = p1ap3_0 - p2[0] - p4[0];
    t3[1] = p1ap3_1 - p2[1] - p4[1];
    // col 4
    t4[0] = p1sp3_0 - p2[1] + p4[1];
    t4[1] = p1sp3_1 + p2[0] - p4[0];
    // col 1 - Top
    *p1++ = p1ap3_0 + p2[0] + p4[0];
    *p1++ = p1ap3_1 + p2[1] + p4[1];

    // COL 2
    twR = tw2[0];
    twI = tw2[1];

    m0 = t2[0] * twR;
    m1 = t2[1] * twI;
    m2 = t2[1] * twR;
    m3 = t2[0] * twI;

    *p2++ = m0 + m1;
    *p2++ = m2 - m3;
    // COL 3
    twR = tw3[0];
    twI = tw3[1];

    m0 = t3[0] * twR;
    m1 = t3[1] * twI;
    m2 = t3[1] * twR;
    m3 = t3[0] * twI;

    *p3++ = m0 + m1;
    *p3++ = m2 - m3;
    // COL 4
    twR = tw4[0];
    twI = tw4[1];

    m0 = t4[0] * twR;
    m1 = t4[1] * twI;
    m2 = t4[1] * twR;
    m3 = t4[0] * twI;

    *p4++ = m0 + m1;
    *p4++ = m2 - m3;

    // first col
    arm_radix8_butterfly_f32( pCol1, L, ( double* )S->pTwiddle, 4u );
    // second col
    arm_radix8_butterfly_f32( pCol2, L, ( double* )S->pTwiddle, 4u );
    // third col
    arm_radix8_butterfly_f32( pCol3, L, ( double* )S->pTwiddle, 4u );
    // fourth col
    arm_radix8_butterfly_f32( pCol4, L, ( double* )S->pTwiddle, 4u );
}

// Processing function for the floating-point complex FFT.
static void arm_cfft_f32( const arm_cfft_instance_f32* S,
    double * p1, uint8_t ifftFlag, uint8_t bitReverseFlag )
{
    uint32_t L = S->fftLen, ll;
    double invL, *pSrc;

    if( ifftFlag == 1u )
    {
        // Conjugate input data
        pSrc = p1 + 1;
        for( ll = 0; ll < L; ll++ )
        {
            *pSrc = -*pSrc;
            pSrc += 2;
        }
    }

    switch( L )
    {
        case 16:
        case 128:
        case 1024:
            arm_cfft_radix8by2_f32( ( arm_cfft_instance_f32* ) S, p1 );
            break;
        case 32:
        case 256:
        case 2048:
            arm_cfft_radix8by4_f32( ( arm_cfft_instance_f32* ) S, p1 );
            break;
        case 64:
        case 512:
        case 4096:
            arm_radix8_butterfly_f32( p1, L, ( double* ) S->pTwiddle, 1 );
            break;
    }

    if( bitReverseFlag )
        arm_bitreversal_32( ( uint32_t* )p1, S->bitRevLength, S->pBitRevTable );

    if( ifftFlag == 1u )
    {
        invL = 1.0f / ( double )L;
        // Conjugate and scale output data
        pSrc = p1;
        for( ll = 0; ll < L; ll++ )
        {
            *pSrc++ *= invL ;
            *pSrc = -( *pSrc ) * invL;
            pSrc++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises fast RFFT.
arm_status arm_rfft_fast_init_f32(
    arm_rfft_fast_instance_f32* S, uint16_t fftLen )
{
    arm_cfft_instance_f32 *Sint;
    // Initialise the default arm status
    arm_status status = ARM_MATH_SUCCESS;
    // Initialise the FFT length
    Sint = &( S->Sint );
    Sint->fftLen = fftLen/2;
    S->fftLenRFFT = fftLen;

    // Initializations of structure parameters depending on the FFT length
    switch( Sint->fftLen )
    {
        case 2048u:
            // Initializations of structure parameters for 2048 point FFT
            // Initialise the bit reversal table length
            Sint->bitRevLength = ARMBITREVINDEXTABLE2048_TABLE_LENGTH;
            // Initialise the bit reversal table pointer
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable2048;
            // Initialise the Twiddle coefficient pointers
            Sint->pTwiddle     = ( double* )twiddleCoef_2048;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_4096;
            break;
        case 1024u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE1024_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable1024;
            Sint->pTwiddle     = ( double* )twiddleCoef_1024;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_2048;
            break;
        case 512u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE_512_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable512;
            Sint->pTwiddle     = ( double* )twiddleCoef_512;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_1024;
            break;
        case 256u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE_256_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable256;
            Sint->pTwiddle     = ( double* )twiddleCoef_256;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_512;
            break;
        case 128u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE_128_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable128;
            Sint->pTwiddle     = ( double* )twiddleCoef_128;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_256;
            break;
        case 64u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE__64_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable64;
            Sint->pTwiddle     = ( double* )twiddleCoef_64;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_128;
            break;
        case 32u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE__32_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable32;
            Sint->pTwiddle     = ( double* )twiddleCoef_32;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_64;
            break;
        case 16u:
            Sint->bitRevLength = ARMBITREVINDEXTABLE__16_TABLE_LENGTH;
            Sint->pBitRevTable = ( uint16_t* )armBitRevIndexTable16;
            Sint->pTwiddle     = ( double* )twiddleCoef_16;
            S->pTwiddleRFFT    = ( double* )twiddleCoef_rfft_32;
            break;
        default:
            // Reporting argument error if fftSize is not valid value
            status = ARM_MATH_ARGUMENT_ERROR;
            break;
    }

    return status;
}

// Performs a fast RFFT calculation.
void arm_rfft_fast_f32( arm_rfft_fast_instance_f32* S,
    double* p, double* pOut, uint8_t ifftFlag )
{
    arm_cfft_instance_f32* Sint = &( S->Sint );
    Sint->fftLen = S->fftLenRFFT / 2;

    // Calculation of Real FFT
    if( ifftFlag )
    {
       // Real FFT compression
       merge_rfft_f32( S, p, pOut );

       // Complex radix-4 IFFT process
       arm_cfft_f32( Sint, pOut, ifftFlag, 1 );
    }
    else
    {
       // Calculation of RFFT of input
       arm_cfft_f32( Sint, p, ifftFlag, 1 );

       // Real FFT extraction
       stage_rfft_f32( S, p, pOut );
    }
}