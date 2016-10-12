// Read the first half of the file as a C string
// Hint fopen, fseek, ftell, fread, malloc, fclose

char* half(char*filename) {
  FILE *f = fopen(filename,"r");
  fseek( f, 0, SEEK_END);
  long halfsize = ftell(f)/2;
  char* result = malloc( halfsize + 1);
  result[halfsize] = '\0';
  rewind(f); //or fseek(f, 0, SEEK_SET);
  fread( result, 1, halfsize, f);
  fclose(f);
  return result;
}
