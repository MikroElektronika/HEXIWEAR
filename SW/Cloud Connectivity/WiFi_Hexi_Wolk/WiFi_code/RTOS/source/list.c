// File: list.c

// Implementation of the lists functionalities used by the kernel.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "list.h"
#include "task.h"

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Initialises a list. Will put xListItem into the list as an end marker.
// Must be called before a list is used.
void vListInitialise( List_t * const pxList )
{
    // Put the end marker into the list.
    pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );
    
    // Put end marker value as the highest possible so it remains at the end.
    pxList->xListEnd.xItemValue = portMAX_DELAY;
    
    // Set the next and previous pointers of the end marker to point to itself.
    pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
    pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );
    
    // Set the number of items to 0.
    pxList->uxNumberOfItems = 0;
}

// Initialises a list item. Will set the container of the item to null.
void vListInitialiseItem( ListItem_t * const pxListItem )
{
    // Ensure the item does not think it is in a list.
    pxListItem->pvContainer = NULL;
}

// Inserts a lit item into a list.
// The item will be inserted according to its value.
void vListInsert( List_t * const pxList, ListItem_t * const pxListItem )
{
    ListItem_t *pxIterator;
    /* const */ TickType_t xValueOfInsertion = pxListItem->xItemValue;
    
    if( xValueOfInsertion == portMAX_DELAY )
    {
        // The position is at the end of the list.
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        // Iterate to the appropriate position.
        for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
            pxIterator->pxNext->xItemValue <= xValueOfInsertion;
            pxIterator = pxIterator->pxNext);
    }
    
    // Put the new item in its place.
    pxListItem->pxNext = pxIterator->pxNext;
    pxListItem->pxPrevious = pxIterator;
    pxIterator->pxNext->pxPrevious = pxListItem;
    pxIterator->pxNext = pxListItem;
    
    // Remember which list the item is in.
    pxListItem->pvContainer = ( void * ) pxList;
    
    // Increase the number of items in the list.
    pxList->uxNumberOfItems++;
}

// Inserts a list item into a list so that it is the last item to be removed
// by a call to listGET_OWNER_OF_NEXT_ENTRY().
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxListItem )
{
    ListItem_t * const pxIndex = pxList->pxIndex;
    
    // Put the new item in its place.
    pxListItem->pxNext = pxIndex;
    pxListItem->pxPrevious = pxIndex->pxPrevious;
    pxIndex->pxPrevious->pxNext = pxListItem;
    pxIndex->pxPrevious = pxListItem;

    // Remember which list the item is in.
    pxListItem->pvContainer = ( void * ) pxList;

    // Increase the number of items in the list.
    pxList->uxNumberOfItems++;
}

// Function to remove the item from its list, if it has one.
UBaseType_t uxListRemove( ListItem_t * const pxListItem )
{
    List_t * const pxList = ( List_t * ) pxListItem->pvContainer;

    if( pxList == NULL )
        return 0;
    
//    PTA_PDOR.B13 = 1;
    
    pxListItem->pxNext->pxPrevious = pxListItem->pxPrevious;

//    PTA_PDOR.B13 = 0;
    pxListItem->pxPrevious->pxNext = pxListItem->pxNext;

    // Make sure that the list index is pointing to a valid item.
    if( pxList->pxIndex == pxListItem )
    {
        pxList->pxIndex = pxListItem->pxPrevious;
    }

    // Make sure the item knows it is not in a list anymore.
    pxListItem->pvContainer = NULL;
    // Decrement the list's item counter.
    pxList->uxNumberOfItems--;

    return pxList->uxNumberOfItems;
}