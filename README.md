# ft_containers

![cpp-stl-standard-template-library1](https://github.com/nousheenali/ft_containers/assets/66158938/f62f8653-91c6-4e48-9714-a972c54b46c3)

[Image reference](https://www.tutorialandexample.com/cpp-stl-standard-template-library)


```bash
./run_tests all     # to run all tests
./run_tests stack   # to run stack tests only
./run_tests vector  # to run vector tests only
./run_tests map     # to run map tests only
```

```bash
#To run individual test files
 c++ {compilation_flags} {namespace} {source_file_location} -o {executable}
 
 example:
 c++ -Werror -std=c++98 -D NAMESPACE=ft tests/stack/constructors.cpp -o ft_exec
 c++ -Werror -std=c++98 -D NAMESPACE=std tests/stack/constructors.cpp -o std_exec
```

![ft_containers](https://user-images.githubusercontent.com/66158938/231119416-ff97cfe7-3873-4866-93e2-9ece61976a3b.gif)



### Concept of container/iterator/algorithm

https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits

### Iterators

- https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
- https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators
- https://codereview.stackexchange.com/questions/198035/implementing-a-custom-iterator-by-inheriting-from-an-existing-iterator-class-and
- https://stackoverflow.com/questions/71737631/what-is-the-design-purpose-of-iterator-traits
- https://stackoverflow.com/questions/6742008/what-are-the-typical-use-cases-of-an-iterator-trait
- DEREFERENCING in reverse iterator : https://devblogs.microsoft.com/oldnewthing/20211112-00/?p=105908


### SFINAE and enable_if
 https://eli.thegreenplace.net/2014/sfinae-and-enable_if/
 
## Vector References
- https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/*/

- building vector container
    https://richardhnguyen.com/articles/rebuild-cpp-vector-p1
    https://www.youtube.com/watch?v=ryRf4Jh_YC0 */

- vector iterators
    https://www.youtube.com/watch?v=F9eDv-YIOQ0*/
    
- Iterator base class
    // https://cplusplus.com/reference/iterator/iterator/



## Map references
- STL_MAP implementation :
  https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_map.h

- RED_BLACK tree implementation :
  https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_tree.h
  
- STL MAP and TREE Standard code
    http://ld2014.scusa.lsu.edu/STL_doc/stl_tree.h
    
- Iterating through a tree
    https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
    

- RED BLACK tree isertion deletion : https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
- bst deletion: https://www.youtube.com/watch?v=cySVml6e_Fc
- redblack tree deletion: https://www.youtube.com/watch?v=w5cvkTXY0vQ&t=2422s


