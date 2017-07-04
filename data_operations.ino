/*class ArrayToCSV
{
  public:
    createarray();
    void append(String str_to_append);
    void dash();
  private:
    int _pin;
}; */


void clean_string_array(String strings_array[], int string_array_size)
{
  for(int i=0; i<string_array_size; i++)
  {
    strings_array[i]= "";
  }
}

String string_array_to_csv_string(String strings_array[], int string_array_size)
{
  String csv_string = "";
  for(int i=0; i<string_array_size; i++)
  {
    csv_string= csv_string + strings_array[i] + ", ";
  }
  return csv_string;
}

/*
String append_to_string_array(array1, array2)
{
  for 
}
*/
