// b) Unrelated to part (a), but as we discussed in class, the indexing pattern (e.g. round-robin or
// chunking) that threads use in a GPU kernel can have a large effect on the performance of the
// GPU kernel. That is, if threads that share a load/store unit access different memory locations,
// the load/store unit might have to make more (or less) requests to the GPU memory.
// Assume a GPU kernel running with a single warp (32 threads); assume 4 contiguous threads
// share a load/store unit. For example threads 0,1,2,3 share a load/store unit, threads 4,5,6,7
// share a load/store unit, etc.
// If all threads access some input array ONCE, accessing a 32 bit integer type, using the following
// indexes, please describe how many memory requests the load/store units across the entire
// warp must make to the GPU memory. You should assume that the input array is large enough
// such that the indexes never go out of bounds. You can assume that the load/store unit fetches
// 16 bytes at a time.

// • if threads index memory using: threadIdx.x (the GPU thread id)
// • if threads index memory using: threadIdx.x + 4
// • if threads index memory using: threadIdx.x / 4 (integer division)
// • if threads index memory using: threadIdx.x * 2
// • if threads index memory using: threadIdx.x * 4

