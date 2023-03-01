/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:59:19 by nali              #+#    #+#             */
/*   Updated: 2023/03/01 10:54:21 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/containers.hpp"
#include <vector>
#include <map>
#include <stack>
#include <__tree>

/*br tree test*/
int main() 
{
    // ft::map<int, int> m1;
	// std::map<int, int>m2;
	// ft::pair<int, int> p;
	// p.first = 1;
	// p.second = 11;
	
    ft::Rb_tree<int> rbt;
    
	
	// bst.insert(8);
	// bst.insert(18);
	// bst.insert(5);
	// bst.insert(15);
	// bst.insert(17);
	// bst.insert(25);
	// bst.insert(40);
	// bst.insert(80);
	// bst.deleteNode(25);
	// bst.prettyPrint();
	// return 0;
}

/*map test*/

// int main(void)
// {
//     std::map<char, int> mp;
//     return (0);
// }

// /*pair test*/

// int main(void)
// {
//     ft::pair <std::string,double> product1;                     // default constructor
//     ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
//     ft::pair <std::string,double> product3 (product2);         //copy constructor

//     ft::pair <std::string,double> product4;
//     product4 = product2; 

//     std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
//     std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
//     std::cout << "The price of " << product3.first << " is $" << product3.second << '\n'; 
//     std::cout << "The price of " << product4.first << " is $" << product4.second << '\n'; 
    
//     // ft::pair<int,char> foo (10,'z');
//     // ft::pair<int,char> bar (90,'a');

//     ft::pair <int,int> foo;
//     ft::pair <int,int> bar;

//     foo = ft::make_pair (10,20);
//     bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

//     std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
//     std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
//     if (foo==bar) std::cout << "foo and bar are equal\n";
//     if (foo!=bar) std::cout << "foo and bar are not equal\n";
//     if (foo< bar) std::cout << "foo is less than bar\n";
//     if (foo> bar) std::cout << "foo is greater than bar\n";
//     if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//     if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
    
//     return (0);
// }
// #define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

// template <typename T>
// void	printSize(ft::vector<T> const &vct,  bool print_content = true)
// {
// 	std::cout << "size: " << vct.size() << std::endl;
// 	std::cout << "capacity: " << vct.capacity()<< std::endl;
// 	std::cout << "max_size: " << vct.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename ft::vector<T>::const_iterator it = vct.begin();
// 		typename ft::vector<T>::const_iterator ite = vct.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << *it << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }

// void	checkErase(ft::vector<std::string> const &vct, ft::vector<std::string>::const_iterator const &it)
// {
// 	static int i = 0;
// 	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
// 	printSize(vct);
// }


// int main(void)
// {
//     std::string choice;
//     std::cout << "Please enter your choice: ";
//     std::cin >> choice;
//     if (choice == "STACK")
//     {
//         std::cout << BLUE << "TESTING FEATURES OF STACK\n" << END;
//         begin_stack_test();
//     }
//     return (0);
// }

/* stack test*/
// int main(void)
// {
//     std::stack<int> s;
//     std::vector<int> v;
//     ft::stack<int> stck;
//     stck.push(3);
//     stck.push(11);
//     stck.push(12);
//     s.push(3);
//     s.push(11);
//     s.push(12);
//     printf("%lu\n", stck.size());
//     ft::stack<int> stck2(stck);
//     std::stack<int> s2(s);
//     ft::stack<int> stck3 = stck;
//     std::stack<int> s3 = s;
//     printf("%d\n", stck3<stck2);
//     printf("%d\n", s3<s2);
// }


// /*vector test*/
// int main(void)
// {

    
//     // default construvtor
//     std::vector<int> vec_s1;
//     ft::vector<int> vec_f1;

//     //fill constructor
//     std::vector<int> vec_s2(5, 13);
//     ft::vector<int> vec_f2(5, 13);
    
//     //copy constructor
//     std::vector<int> vec_s3(vec_s2);
//     ft::vector<int> vec_f3(vec_f2);
    
//     //iterators
//     std::vector<int>::iterator it1_b,it1_e;
//     ft::vector<int>::iterator it2_b,it2_e;
//     it1_b =vec_s3.begin(); it1_e = vec_s3.end();
//     it2_b =vec_f3.begin(); it2_e =  vec_f3.end();
//     //range constructor
//     std::vector<int> vec_s4(it1_b,it1_e);
//     ft::vector<int> vec_f4(it2_b,it2_e);

//     /*---------------------------------------------*/
//     std::cout << "Check iterators\n";
//     while(it1_b != it1_e)
//     {
//         std::cout << *it1_b << ' ';
//         it1_b++;
//     }
//     std::cout << std::endl;
//     while(it2_b !=  it2_e)
//     {
//         std::cout << *it2_b << ' ';
//         it2_b++;
//     }
//     /*---------------------------------------------*/
//     std::cout << "\nCheck range constructor\n";
//     for(int i= 0; i < vec_s4.size(); i++ )
//         std::cout << vec_s4[i]<< ' ';
//     std::cout << std::endl;
//     for( int j= 0; j < vec_f4.size(); j++ )
//         std::cout << vec_f4[j]<< ' ';
//      std::cout << std::endl;
//     //copy assignment
//     std::vector<int> vec_s5 = vec_s3;
//     ft::vector<int> vec_f5 = vec_f4;

//     /*---------------------------------------------*/
//     std::cout << "\nCheck copy assignment\n";
//     for( int j= 0; j < vec_f5.size(); j++ )
//         std::cout << vec_f5[j]<< ' ';
//     std::cout << std::endl;

//     /*---------------------------------------------*/
//     std::cout << "\nCheck assign()\n";
//     std::cout << vec_s5.size() <<std::endl;
//     vec_s5.assign(6,100);
//     std::cout << vec_s5.size() <<std::endl;

//     std::cout << vec_f5.size() <<std::endl;
//     vec_f5.assign(6,100);
//     std::cout << vec_f5.size() <<std::endl;

//     /*---------------------------------------------*/
//     std::cout << "\nCheck assign() iterator range\n";
//     it1_b =vec_s3.begin(); it1_e = vec_s3.end();
//     it2_b =vec_f3.begin(); it2_e =  vec_f3.end();
    
//     std::vector<int> vec_s6(9, 11);
//     std::cout << vec_s6.size() <<std::endl;
//     for( int j= 0; j < vec_s6.size(); j++ )
//         std::cout << vec_s6[j]<< ' ';
//     std::cout << std::endl;
//     vec_s6.assign(it1_b, it1_e);
//     std::cout << vec_s6.size() <<std::endl;
//     for( int j= 0; j < vec_s6.size(); j++ )
//         std::cout << vec_s6[j]<< ' ';
//     std::cout << std::endl;

//     ft::vector<int> vec_f6(9, 11);
//     std::cout << vec_f6.size() <<std::endl;
//     for( int j= 0; j < vec_f6.size(); j++ )
//         std::cout << vec_f6[j]<< ' ';
//     std::cout << std::endl;
//     vec_f6.assign(it2_b, it2_e);
//     std::cout << vec_f6.size() <<std::endl;
//     for( int j= 0; j < vec_f6.size(); j++ )
//         std::cout << vec_f6[j]<< ' ';
//     std::cout << std::endl;

//     /*---------------------------------------------*/
//     std::cout << "\nCheck at()\n";
//     vec_s6.at(3) = 17;
//     for( int j= 0; j < vec_s6.size(); j++ )
//         std::cout << vec_s6[j]<< ' ';
//     std::cout << std::endl;

//     vec_f6.at(3) = 17;
//     for( int j= 0; j < vec_f6.size(); j++ )
//         std::cout << vec_f6[j]<< ' ';
//     std::cout << std::endl;


//     /*---------------------------------------------*/
//     std::cout << "\nCheck insert() single\n";
//     std::vector<int> vec_s7(5, 10);
//     ft::vector<int> vec_f7(5, 10);
//     for( int j= 0; j < vec_s7.size(); j++ )
//         std::cout << vec_s7[j]<< ' ';
//     std::cout << std::endl;

//     std::vector<int>::iterator it7;
//     it7 = vec_s7.begin();
//     it7++;
//     it7++;
//     vec_s7.insert(it7, 90);
//     for( int j= 0; j < vec_s7.size(); j++ )
//         std::cout << vec_s7[j]<< ' ';
//     std::cout << std::endl;

//     for( int j= 0; j < vec_f7.size() ; j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;
//     ft::vector<int>::iterator itf7;
//     itf7 = vec_f7.begin();
//     itf7++;
//     itf7++;
//     vec_f7.insert(itf7,90);
//     for( int j= 0; j < vec_f7.size(); j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;

//     std::cout << "\nCheck insert() multiple\n";
//     itf7 = vec_f7.begin();
//     itf7++;
//     itf7++;
//     vec_f7.insert(itf7, 3, 99);
//     for( int j= 0; j < vec_f7.size(); j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;

//     std::cout << "\nCheck insert() iter range \n";
//     it2_b =vec_f3.begin(); it2_e =  vec_f3.end();
//     itf7 = vec_f7.begin();
//     itf7++;
//     itf7++;
//     vec_f7.insert(itf7, it2_b, it2_e);
//     for( int j= 0; j < vec_f7.size(); j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;

//     itf7 = vec_f7.begin();
//     itf7++;
//     itf7++;
//     vec_f7.erase(itf7);
//     for( int j= 0; j < vec_f7.size(); j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;

//     std::cout << "\nCheck erase\n";
//     ft::vector<int>::iterator itf8;
//     itf7 = vec_f7.begin();
//     itf7++;
//     itf7++;
//     itf8 = vec_f7.begin();
//     itf8++;
//     itf8++;
//     itf8++;
//     itf8++;
//     itf8++;
//     vec_f7.erase(itf7, itf8);
//     for( int j= 0; j < vec_f7.size(); j++ )
//         std::cout << vec_f7[j]<< ' ';
//     std::cout << std::endl;


//     std::cout << "\nCheck relational operators\n";
//     ft::vector<int> alice;
//     alice.push_back(1); alice.push_back(2);alice.push_back(3);
//     ft::vector<int> eve;
//     eve.push_back(1); eve.push_back(2);eve.push_back(3);
 
//     std::cout << std::boolalpha;
 
//     // Compare non equal containers
//     std::cout << "alice == eve returns " << (alice == eve) << '\n';
//     alice.push_back(4);
//     std::cout << "alice == eve returns " << (alice == eve) << '\n';
//     std::cout << "alice != eve returns " << (alice != eve) << '\n';




//     return (0);
// }

