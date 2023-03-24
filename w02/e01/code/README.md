Compile with:
  ```bash
  make <name><flag> 
  ```
Where `<name>` is the name of the sourcecode without extention, and <flag> can be one of: `O0, O1, O2, O3, Os, Ofast`.

The jobscript outputs the optimizer flag and execution time to stdout in csv format.
plots.py reads the output.log and creates a barplot using the mean execution time per flag.
