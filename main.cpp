#include "list.h"
#include<list>
bool p(int n) { return n % 2 == 1; }
int main() {
	nstd::list<int> ls;
	nstd::list<int> ls2(2);
	nstd::list<int>ls3(2, 3);
	nstd::list<int>ls4(ls3);
	std::cout << " ls4 size, l5 size- " << ls4.size() << ", ";
	nstd::list<int> ls5{1, 2, 3 ,4};
	std::cout << ls5.size() << " "<<std::endl;
	nstd::list<int> ls6(std::move(ls2));
	nstd::list<int> ls7(++ls5.begin(), ls5.end());
	std::cout << "  ls7-" << ls7 << std::endl;
	std::cout << "comparison ls2<=ls3 - " << (ls2 <= ls3) << " comparison ls5<ls3 - " << (ls5 < ls3) << std::endl;
	std::cout << "ls5- " << ls5 << std::endl;
	std::cout << "emptyls2 - " << ls2.empty() << " ,empty ls5- " << ls5.empty() << " max_size ls5- " << ls5.max_size() << std::endl;
	ls5.assign(3, 2);
	ls2.assign(ls3.begin(), ls3.end());
	std::cout << " assign ls5(3,2) -  " << ls5 <<" ls5  size- "<<ls5.size()<< " assign ls2(ls3)-" << ls2 << std::endl;
	swap(ls5, ls2);
	std::cout << " swap ls5,ls2 - " << ls5  <<"  size " << ls5.size() << " - " << ls2 << std::endl;
	ls2.push_back(4);
	std::cout << " push_back ls2 -" << ls2 << std::endl;
	ls2.push_front(4);
	std::cout << " push front ls2- " << ls2 << std::endl;
	ls2.pop_back();
	std::cout << " pop_back ls2- " << ls2 << std::endl;
	ls2.pop_front();
	std::cout <<  "pop_front ls2 -" << ls2 << std::endl;
	ls7.insert(--ls7.end(), 7);
	std::cout << " insert ls7   " << ls7 << std::endl;
	ls7.insert(--ls7.end(), 2, 8);
	std::cout << " insert ls7 " << ls7 << " size - "<<ls7.size()<<std::endl;
	ls5.insert(ls5.begin(), ls7.begin(), ++ls7.begin());
	std::cout << " insert ls5 " << ls5 << " size " << ls5.size()<< std::endl;
	ls5.emplace(ls5.end(), 7);
	std::cout << " emplace ls5 " << ls5 << " size " << ls5.size() << std::endl;
	ls5.emplace_back(7);
	std::cout << " emplace back ls5 " << ls5 << std::endl;
	ls5.erase(ls5.begin());
	std::cout << " erase ls5 " << ls5 << std::endl;
	ls5.remove(7);
	std::cout << " remove ls5 " << ls5 << std::endl;
	ls5.remove_if(p);
	std::cout << " remove_if ls5 " << ls5 << std::endl;
	ls7.reverse();
	std::cout << " reverse ls7 " << ls7 << "  size-"<<ls7.size()<< std::endl;
	ls7.resize(3);
	std::cout << " resize ls " << ls7 << std::endl;
	ls7.splice(--ls7.end(),ls2);
	std::cout << " splice ls7,ls5  " << ls7 << std::endl;
	ls4.resize(1);
	ls4.splice(ls4.begin(), ls7, ++ls7.begin());
	std::cout << " splice ls4,ls7  " << ls4 << std::endl;
	ls4.splice(ls4.begin(), ls2.begin(), ls2.end());
	std::cout << " splice ls4,ls2  " << ls4 << std::endl;
	/*std::list<int> lst{1,2,6,9};
	std::list<int> lst2{ 5,7,8};
	lst.splice(++lst.begin(),lst2,lst2.begin(),lst2.end());
	std::copy ( lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));*/
}