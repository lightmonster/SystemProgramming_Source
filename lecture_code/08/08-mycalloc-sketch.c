void* mycalloc(size_t count, size_t size) {
  size_t total  = count * size;
  void* result = malloc(total);
  if(!result) return NULL;
  memset(result, 0, total);
  memset(result,total,0); // Ooops
  return result;
}

void* realloc(void* oldptr, size_t newsize) {
   if(oldptr == NULL) return malloc(newsize);

   void * ptr = malloc( newsize);
   for(int i = 0; i < oldsize; i++) ptr[i] = oldptr[i];
   //Gotchas?
   // need to remember original size when malloc is called!
   // min(newsize,oldsize)

}
   
