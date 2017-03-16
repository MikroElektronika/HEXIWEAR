// File: list.h

// Interface of the lists functionalities used by the kernel.

#ifndef _list_h_
#define _list_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "portmacro.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// Sets the owner (TCB) of the given list item.
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )                         \
    ( ( pxListItem )->pvOwner = ( void * ) pxOwner )

// Returns the owner (TCB) of the given list item.
#define listGET_LIST_ITEM_OWNER( pxListItem )                                  \
    ( ( pxListItem )->pvOwner )

// Set the value of the given list item.
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )                          \
    ( ( pxListItem )->xItemValue = ( xValue ) )

// Returns the value of the given list item.
#define listGET_LIST_ITEM_VALUE( pxListItem )                                  \
    ( ( pxListItem )->xItemValue )
    
// Returns the value of the list item at the head of the given list.
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )                             \
    ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

// Returns the list item at the head of the given list.
#define listGET_HEAD_ENTRY( pxList )                                           \
    ( ( ( pxList )->xListEnd ).pxNext )

// Returns the list item after the given list item.
#define listGET_NEXT( pxListItem )                                             \
    ( ( pxListItem )->pxNext )

// Returns the list item that marks the end of the given list.
#define listGET_END_MARKER( pxList )                                           \
    ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )

// Determines whether the given list is empty.
#define listLIST_IS_EMPTY( pxList )                                            \
    ( ( BaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) )

// Returns the number of elements in the given list.
#define listCURRENT_LIST_LENGTH( pxList )                                      \
    ( ( pxList )->uxNumberOfItems )

// Returns the owner of the next entry in the given list.
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )                           \
{                                                                              \
    List_t * const pxConstList = ( pxList );                                   \
                                                                               \
    ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;               \
    if( ( void * ) ( pxConstList )->pxIndex ==                                 \
        ( void * ) &( ( pxConstList )->xListEnd ) )                            \
    {                                                                          \
        ( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;           \
    }                                                                          \
    ( pxTCB ) = ( pxConstList )->pxIndex->pvOwner;                             \
}

// Returns the owner of the first item in the given list.
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )                                  \
    ( (&( ( pxList )->xListEnd ))->pxNext->pvOwner )

// Determines whether the given item is contained in the given list.
#define listIS_CONTAINED_WITHIN( pxList, pxListItem )                          \
    ( ( BaseType_t ) ( ( pxListItem )->pvContainer == ( void * ) ( pxList ) ) )

// Returns the list that contains the given item.
#define listLIST_ITEM_CONTAINER( pxListItem )                                  \
    ( ( pxListItem )->pvContainer )

// Determines whether the given list is initialized.
#define listLIST_IS_INITIALISED( pxList )                                      \
    ( ( pxList )->xListEnd.xItemValue == portMAX_DELAY )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// List item structure. All real objects in the list must be of this type.
typedef struct xLIST_ITEM
{
    // Value being listed, used to sort the list.
    TickType_t xItemValue;
    // Pointer to next list item.
    struct xLIST_ITEM *pxNext;
    // Pointer to previous list item.
    struct xLIST_ITEM *pxPrevious;
    // Pointer to the object (TCB) that contains the list item.
    void *pvOwner;
    // Pointer to the list in which this item is placed.
    void *pvContainer;
} ListItem_t;

// Mini list item structure. Used as the end marker in the list.
typedef struct xMINI_LIST_ITEM
{
    TickType_t xItemValue;
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevious;
} MiniListItem_t;

// Structure of the list itself, used as the queue by the scheduler.
typedef struct xLIST
{
    UBaseType_t uxNumberOfItems;
    // Last item returned by a call of listGET_OWNER_OF_NEXT_ENTRY().
    ListItem_t *pxIndex;
    // End marker.
    MiniListItem_t xListEnd;
} List_t;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Initialises a list. Will put xListItem into the list as an end marker.
// Must be called before a list is used.
void vListInitialise( List_t * const pxList );

// Initialises a list item. Will set the container of the item to null.
void vListInitialiseItem( ListItem_t * const pxListItem );

// Inserts a lit item into a list.
// The item will be inserted according to its value.
void vListInsert( List_t * const pxList, ListItem_t * const pxListItem );

// Inserts a list item into a list so that it is the last item to be removed
// by a call to listGET_OWNER_OF_NEXT_ENTRY().
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxListItem );

// Function to remove the item from its list, if it has one.
UBaseType_t uxListRemove( ListItem_t * const pxListItem );

#endif