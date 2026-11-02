#if defined _INC_SSI_QUEUE
    #endinput
#endif
#define _INC_SSI_QUEUE

/**
 * Queues hand out the rows of an array and take them back first in, first out.
 * The array is declared with the queue and read and written as any array, a row
 * at a time, with the fields of an enum when it has two dimensions:
 *
 *     #include <SSI\queue>
 *
 *     enum E_TAXI_CALL {
 *         E_TAXI_CALL_PLAYER,
 *         E_TAXI_CALL_TIME
 *     }
 *
 *     static
 *         Queue:TaxiCall<MAX_PLAYERS, E_TAXI_CALL>
 *     ;
 *
 *     new
 *         TaxiCall:row = Queue_Push(TaxiCall)
 *     ;
 *
 *     TaxiCall[row][E_TAXI_CALL_PLAYER] = playerid;
 *     TaxiCall[row][E_TAXI_CALL_TIME] = gettime();
 *
 *     if (!Queue_IsEmpty(TaxiCall)) {
 *         row = Queue_Pop(TaxiCall);
 *     }
 *
 * The rows carry the tag of the queue, as the ids of a collection do, and the
 * first dimension of the array takes that tag, so a row is the only index that
 * reaches it without a warning. The size takes any tag. A tag before the
 * keyword tags the cells, as `Vehicle:Queue:Respawn<MAX_VEHICLES>`.
 *
 * The rows go round the array, which has one row more than the size. A row
 * taken out keeps its cells until the next one is taken out, so a walk of a tree
 * in breadth reads a row after taking it out while it pushes its children.
 */

/**
 * # Header
 */

#if !defined SSI@row
    stock
        SSI@row
    ;
#endif

/**
 * Makes `Queue:queue<>` in the forwards below a plain parameter, so the editor
 * shows a queue the way it is used. The declaration takes its place after them.
 */
#define Queue:%0<%1> %0

/**
 * # Functions
 */

/**
 * @brief      Empty the queue.
 *
 * The next row handed out is the first of the array.
 *
 * @param      queue  The queue.
 */
forward Queue_Clear(Queue:queue<>);
#define Queue_Clear(%0) (%0@SSI_head = %0@SSI_tail = 0)

/**
 * @brief      Hand out a row, last in the queue.
 *
 * The row keeps what it held before, so every field it uses is written.
 *
 * @param      queue  The queue.
 *
 * @return     - the row, with the tag of the queue
 *             - `-1` with that tag, when the queue is full
 */
forward Queue_Push(Queue:queue<>);
#define Queue_Push(%0) ((SSI@row = %0@SSI_tail) == sizeof %0 - 1 ? (%0@SSI_head == 0 ? (%0:-1) : (%0@SSI_tail = 0, (%0:SSI@row))) : (++%0@SSI_tail == %0@SSI_head ? (%0@SSI_tail = SSI@row, (%0:-1)) : (%0:SSI@row)))

/**
 * @brief      Take out the first row.
 *
 * The row keeps its cells until the next row is taken out.
 *
 * @param      queue  The queue.
 *
 * @return     - the row, with the tag of the queue
 *             - `-1` with that tag, when the queue is empty
 */
forward Queue_Pop(Queue:queue<>);
#define Queue_Pop(%0) (%0@SSI_head == %0@SSI_tail ? (%0:-1) : (%0@SSI_head++ == sizeof %0 - 1 ? (%0@SSI_head = 0, (%0:(sizeof %0 - 1))) : (%0:(%0@SSI_head - 1))))

/**
 * @brief      How many rows are in the queue.
 *
 * @param      queue  The queue.
 */
forward Queue_Size(Queue:queue<>);
#define Queue_Size(%0) (%0@SSI_tail < %0@SSI_head ? %0@SSI_tail - %0@SSI_head + sizeof %0 : %0@SSI_tail - %0@SSI_head)

/**
 * @brief      Whether the queue has no row.
 *
 * @param      queue  The queue.
 */
forward bool:Queue_IsEmpty(Queue:queue<>);
#define Queue_IsEmpty(%0) (%0@SSI_head == %0@SSI_tail)

/**
 * # Declaration
 */

#undef Queue

/**
 * Declares the queue `%0` and its array, for `%1` rows of one cell, or of the
 * enum `%4`, static when the declaration is. The array has a row more, so the
 * row taken out last is never handed out again before the next is taken out,
 * and a full queue is told from an empty one by `head` and `tail` alone. `head`
 * is the first row and `tail` the next row to hand out.
 *
 *     static
 *         Queue:TaxiCall<MAX_PLAYERS, E_TAXI_CALL>
 *     ;
 */
#define Queue:%0<%1> SSI_QUEUE_DECLARE_A:%0|||%1,,|||

#define SSI_QUEUE_DECLARE_A:%0|||%1,%4,%5||| SSI_QUEUE_DECLARE_B%5X|||%0|||%1|||%4|||
#define SSI_QUEUE_DECLARE_BX|||%0|||%1|||%4||| %0[%0:(_:(%1) + 1)], %0@SSI_head, %0@SSI_tail
#define SSI_QUEUE_DECLARE_B,X|||%0|||%1|||%4||| %0[%0:(_:(%1) + 1)][%4], %0@SSI_head, %0@SSI_tail
