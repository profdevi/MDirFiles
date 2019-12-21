# MDirFiles
Tool for deleting, keeping, and printing out files with extensions recursively from a working directory

  usage:  MDirFiles [-?][-list][-del|[-keep] <extensions>*
           v1.0 copyright Comine.com

      -list     :  list files with extensions
      -del      :  delete files with extensions
      -keep     :  delete all files except those with extensions
      -cat      :  print out contents all files with extensions
      -cathead  :  print out contents all files with extensions with header

   examples:
   
       1)   List all .h .cpp files
            C:> MDirFiles -list .h .cpp

       2)   Delete all .h .cpp files
            C:> MDirFiles -del .h .cpp

       3)   Kepp only .h .cpp files.  Delete all others
            C:> MDirFiles -keep .h .cpp


