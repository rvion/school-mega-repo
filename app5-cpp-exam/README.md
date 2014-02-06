## Tp de cpp

    Rémi Vion

```c++
#include <iostream>
#include "twice.hpp"
#include "nth.hpp"
#include "range_nth.hpp"
#include <vector>
#include <iterator>

//                                    Rémi Vion
//                                   18-11-2013 
//                       TP Noté C++ Avancé, Template programming
//            all code can be found in https://github.com/rvion/tp_cpp_app5_final
//
int main(int argc, char ** argv) 
{
    /*
    //                                QUESTION 1
    //
    // ======== PROP 1
        // default constructible            // -----> Pas de code correspondant -> n'est pas implémenté
        // copy constructible               // -----> twice_iterator( BaseIterator i) : base_(i) {}
        // copy assignable                  // -----> Pas de code, implémentation IMPLICITE (ou pas, selon la version de gcc utilisée)
        // destructible                     // -----> Pas de code, implémentation IMPLICITE
    // ======== PROP 2
        // comparable with (==)             // -----> bool operator==(twice_iterator const& rhs)
        // comparable with (!=)             // -----> bool operator!=(twice_iterator const& rhs)
    // ======== PROP3
        //dereferencable as an r-value      // -----> pointer operator->()
    // ======== PROP4
        //dereferencable as an l-value      // -----> Pas de code correspondant -> n'est pas implémenté
    // ======== PROP5
        //Can be incremented                // -----> twice_iterator operator++(int)
                                                      twice_iterator& operator++()

    */
    //                               QUESTION 2
    //
    std::vector<int> v; for(int i = 0; i< 5; ++i) v.push_back(i);
    typedef twice_iterator<std::vector<int>::iterator> it;
    // ======== PROP 1
    // twice_iterator<std::vector<int>::iterator> default_constructible; // default constructible
                                                 // -----> ERROR: class is not default-constructible
    it it1(v.begin());  // copy constructible
    it it2(it1);                                 // -----> OK      
    it it3(v.begin()); // copy assignable
    it it4 = it3;                                // -----> OK (/!\ IMPLICITE pas compatible avec anciennes versions de gcc)
    { it it5(it4);}    // destructible           // -----> OK
    // ======== PROP 2
    bool a(it4 == it3); // comparable with (==) // -----> OK
    bool b(it4 != it3); // comparable with (!=) // -----> OK
    // ======== PROP3
    int c = *it3; //dereferencable as an r-value
    it3.operator->();                           // -----> OK
    // ======== PROP4
    //*it3 = 1; //dereferencable as an l-value  // -----> ERROR not mutable
    // ======== PROP5
    ++it3; //Can be incremented                 // -----> ok
    it3++;                                      // -----> ok
    *it3++;                                     // -----> ok
    
    //
    //                               QUESTION 3 
    //
    // d'après le code de l'iterator :
    //   base_++;                           ---> BaseIterator doit être incrémentable
    //   base_(i)                           ---> BaseIterator doit être copy-contructible
    //   base_.operator->();                ---> BaseIterator doit être right-dereferençable
    //   base_ != rhs.base_;                ---> BaseIterator doit être (!=) comparable
    //   base_ == rhs.base_;                ---> BaseIterator doit être (==) comparable
    //   implicite: être destructible       ---> BaseIterator doit être destructible

    //
    //                               QUESTION 4
    //
    std::vector<int> v1; for(int i = 0; i< 5; ++i) v1.push_back(i);
    typedef every_nth_iterator<std::vector<int>::iterator, 2> nth;
    // ======== PROP 1
    nth test; // default constructible              // -----> ERROR: class is not default-constructible
    nth nth1(v.begin());  // copy constructible
    nth nth2(nth1);                                 // -----> OK      
    nth nth3(v.begin()); // copy assignable
    nth nth4 = nth3;                                // -----> OK (/!\ IMPLICITE pas compatible avec anciennes versions de gcc)
    { nth nth5(nth4);}    // destructible           // -----> OK
    // ======== PROP 2
    bool d(nth4 == nth3); // comparable with (==)   // -----> OK
    bool e(nth4 != nth3); // comparable with (!=)   // -----> OK
    // ======== PROP3
    int f = *nth3; //dereferencable as an r-value
    nth3.operator->();                              // -----> OK
    // ======== PROP4
    *nth3 = 1; //dereferencable as an l-value       // -----> OK
    // ======== PROP5
    ++nth3; //Can be incremented                    // -----> OK
    nth3++;                                         // -----> OK
    *nth3++;                                        // -----> OK
                
   //
   //                                QUESTION 5
   //
   // les limititations de cet itérateurs sont:
   //    * qu'il faut instancier plusieurs nth-itérateurs manuellement ce qui est fastidieux 
   //    * ET SURTOUT, que ça peut SEGFAULTEEEEEEEEER.
   //      exemple:
   //            std::vector<int> v2; for(int i = 0; i< 5; ++i) v2.push_back(i);
   //            every_nth_iterator<std::vector<int>::iterator, 2> begin(v2.begin());
   //            every_nth_iterator<std::vector<int>::iterator, 2> end(v2.end());
   //            every_nth_iterator<std::vector<int>::iterator, 2> nit;
   //            
   //            for (nit = begin; nit != end; ++nit)
   //                std::cout << *nit << std::endl;                   <--- SEGFAULT
   //

   //
   //                                QUESTION 6
   //
   
   // On peut maintenant écrire:    
   std::vector<int> v2; for(int i = 0; i< 5; ++i) v2.push_back(i);
    typedef every_nth_range<std::vector<int>::iterator, 2> Range;
    Range range(v2.begin(), v2.end());
    Range::nth nit;
    for (nit = range.begin(); nit != range.end(); ++ nit) 
        std::cout << *nit << std::endl;
    
    // Ce qui est fort, c'est que même en passant v.end() quand on initialise la range
    // le range.end() retournera un itérator sur le dernier élément dont 
    // l'index est congru à 0 modulo n, et ça, c'est bien pratique.
}
```