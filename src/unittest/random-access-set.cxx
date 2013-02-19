#include <stdexcept>

#include "random-access-set.hxx"

inline void test(const bool& pred) {
    if(!pred) throw std::runtime_error("Test failed.");
}

inline void fail() {
    throw std::runtime_error("Test failed.");
}

typedef andres::RandomAccessSet<int> Set;
typedef Set::const_iterator ConstIterator;
typedef Set::iterator Iterator;
typedef Set::const_iterator ConstIterator;
typedef Set::reverse_iterator ReverseIterator;
typedef Set::const_reverse_iterator ConstReverseIterator;

typedef andres::RandomAccessSet<int, std::greater<int> > SetG;
typedef Set::const_iterator ConstIteratorG;
typedef Set::iterator IteratorG;
typedef Set::const_iterator ConstIteratorG;
typedef Set::reverse_iterator ReverseIteratorG;
typedef Set::const_reverse_iterator ConstReverseIteratorG;

int main() {
    // construction 
    {
        Set s;
        test(s.empty());
        test(s.size() == 0);
        test(s.begin() == s.end());
        test(s.rbegin() == s.rend());

        Set t(s); 
        test(t.size() == s.size());
    }

    // assignment
    {
        int data[] = {1, 2, 0, 2};
        Set s(data, data + 4);
        s = s;

        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 0);
        test(s[1] == 1);
        test(s[2] == 2);
        test(s.end() - s.begin() == 3);
        test(s.rend() - s.rbegin() == 3);

        int otherData[] = {2, 5, 40, 2, 12};
        Set t(otherData, otherData + 5);
        t = s;

        test(!t.empty());
        test(t.size() == 3);
        test(t[0] == 0);
        test(t[1] == 1);
        test(t[2] == 2);
        test(t.end() - t.begin() == 3);
        test(t.rend() - t.rbegin() == 3);
    }

    // access using 'operator[]', 'find' and iterators
    {
        int data[] = {1, 2, 0, 2};
        Set s(data, data + 4);

        // operator[]
        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 0);
        test(s[1] == 1);
        test(s[2] == 2);
        test(s.end() - s.begin() == 3);
        test(s.rend() - s.rbegin() == 3);

        // find
        test(*s.find(0) == 0);
        test(*s.find(1) == 1);
        test(*s.find(2) == 2);
        test(s.find(0) == s.begin());
        test(s.find(1) == s.begin() + 1);
        test(s.find(2) == s.begin() + 2);
        test(s.find(3) == s.end());

        // iterators
        size_t j = 0;
        for(Iterator it = s.begin(); it != s.end(); ++it, ++j) {
            test(*it == j);
        }

        j = 0;
        for(ConstIterator it = s.begin(); it != s.end(); ++it, ++j) {
            test(*it == j);
        }

        j = 2;
        for(ReverseIterator it = s.rbegin(); it != s.rend(); ++it, --j) {
            test(*it == j);
        }

        j = 2;
        for(ConstReverseIterator it = s.rbegin(); it != s.rend(); ++it, --j) {
            test(*it == j);
        }
    }

    // access to set with std::greater using 'operator[]', 'find' and iterators
    {
        int data[] = {1, 2, 0, 2};
        SetG s(data, data + 4);

        // operator[]
        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 2);
        test(s[1] == 1);
        test(s[2] == 0);
        test(s.end() - s.begin() == 3);
        test(s.rend() - s.rbegin() == 3);

        // find
        test(*s.find(0) == 0);
        test(*s.find(1) == 1);
        test(*s.find(2) == 2);
        test(s.find(0) == s.begin() + 2);
        test(s.find(1) == s.begin() + 1);
        test(s.find(2) == s.begin());
        test(s.find(3) == s.end());

        // iterators
        size_t j = 2;
        for(IteratorG it = s.begin(); it != s.end(); ++it, --j) {
            test(*it == j);
        }

        j = 2;
        for(ConstIteratorG it = s.begin(); it != s.end(); ++it, --j) {
            test(*it == j);
        }

        j = 0;
        for(ReverseIteratorG it = s.rbegin(); it != s.rend(); ++it, ++j) {
            test(*it == j);
        }

        j = 0;
        for(ConstReverseIteratorG it = s.rbegin(); it != s.rend(); ++it, ++j) {
            test(*it == j);
        }
    }

    // insert
    {
        typedef std::pair<ConstIterator, bool> Pair;
        Set s;
        Pair p = s.insert(10);

        test(!s.empty());
        test(s.size() == 1);
        test(s[0] == 10);
        test(p.first == s.begin());
        test(*(p.first) == 10);
        test(p.second == true); // inserted

        p = s.insert(10);

        test(!s.empty());
        test(s.size() == 1);
        test(s[0] == 10);
        test(p.first == s.begin());
        test(*(p.first) == 10);
        test(p.second == false); // not inserted

        p = s.insert(1);

        test(!s.empty());
        test(s.size() == 2);
        test(s[0] == 1);
        test(s[1] == 10);
        test(*(p.first) == 1);
        test(p.second == true); // inserted

        p = s.insert(1);

        test(!s.empty());
        test(s.size() == 2);
        test(s[0] == 1);
        test(s[1] == 10);
        test(*(p.first) == 1);
        test(p.second == false); // not inserted

        p = s.insert(20);

        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 1);
        test(s[1] == 10);
        test(s[2] == 20);
        test(*(p.first) == 20);
        test(p.second == true); // inserted

        p = s.insert(20);

        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 1);
        test(s[1] == 10);
        test(s[2] == 20);
        test(*(p.first) == 20);
        test(p.second == false); // not inserted

        int data[] = {5, 15, 5, 15};
        s.insert(data, data + 4);
        test(s.size() == 5);
        test(s[0] == 1);
        test(s[1] == 5);
        test(s[2] == 10);
        test(s[3] == 15);
        test(s[4] == 20);

        s.insert(s.begin() + 1, 0);
        test(s[0] == 0);
        test(s[1] == 1);
        test(s[2] == 5);
        test(s[3] == 10);
        test(s[4] == 15);
        test(s[5] == 20);
    }
    
    // insert with std::greater
    {
        typedef std::pair<ConstIteratorG, bool> PairG;
        SetG s;
        PairG p = s.insert(10);

        test(!s.empty());
        test(s.size() == 1);
        test(s[0] == 10);
        test(p.first == s.begin());
        test(*(p.first) == 10);
        test(p.second == true); // inserted

        p = s.insert(10);

        test(!s.empty());
        test(s.size() == 1);
        test(s[0] == 10);
        test(p.first == s.begin());
        test(*(p.first) == 10);
        test(p.second == false); // not inserted

        p = s.insert(1);

        test(!s.empty());
        test(s.size() == 2);
        test(s[0] == 10);
        test(s[1] == 1);
        test(*(p.first) == 1);
        test(p.second == true); // inserted

        p = s.insert(1);

        test(!s.empty());
        test(s.size() == 2);
        test(s[0] == 10);
        test(s[1] == 1);
        test(*(p.first) == 1);
        test(p.second == false); // not inserted

        p = s.insert(20);

        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 20);
        test(s[1] == 10);
        test(s[2] == 1);
        test(*(p.first) == 20);
        test(p.second == true); // inserted

        p = s.insert(20);

        test(!s.empty());
        test(s.size() == 3);
        test(s[0] == 20);
        test(s[1] == 10);
        test(s[2] == 1);
        test(*(p.first) == 20);
        test(p.second == false); // not inserted

        int data[] = {5, 15, 5, 15};
        s.insert(data, data + 4);
        test(s.size() == 5);
        test(s[0] == 20);
        test(s[1] == 15);
        test(s[2] == 10);
        test(s[3] == 5);
        test(s[4] == 1);

        s.insert(s.begin() + 1, 0);
        test(s[0] == 20);
        test(s[1] == 15);
        test(s[2] == 10);
        test(s[3] == 5);
        test(s[4] == 1);
        test(s[5] == 0);
    }

    // erase(key)
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);

        s.erase(1);
        test(s.size() == 4);
        test(s[0] == 5);
        test(s[1] == 10);
        test(s[2] == 15);
        test(s[3] == 20);

        s.erase(10);
        test(s.size() == 3);
        test(s[0] == 5);
        test(s[1] == 15);
        test(s[2] == 20);

        s.erase(20);
        test(s.size() == 2);
        test(s[0] == 5);
        test(s[1] == 15);

        s.erase(5);
        test(s.size() == 1);
        test(s[0] == 15);

        s.erase(15);
        test(s.size() == 0);

        s.erase(1);
        test(s.size() == 0);
    }

    // erase(key) with std::greater
    {
        int data[] = {5, 10, 15, 20};
        SetG s(data, data + 4);

        s.erase(1);
        test(s.size() == 4);
        test(s[3] == 5);
        test(s[2] == 10);
        test(s[1] == 15);
        test(s[0] == 20);

        s.erase(10);
        test(s.size() == 3);
        test(s[2] == 5);
        test(s[1] == 15);
        test(s[0] == 20);

        s.erase(20);
        test(s.size() == 2);
        test(s[1] == 5);
        test(s[0] == 15);

        s.erase(5);
        test(s.size() == 1);
        test(s[0] == 15);

        s.erase(15);
        test(s.size() == 0);

        s.erase(1);
        test(s.size() == 0);
    }

    // erase(iterator)
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);

        s.erase(s.find(10));
        test(s.size() == 3);
        test(s[0] == 5);
        test(s[1] == 15);
        test(s[2] == 20);

        s.erase(s.find(20));
        test(s.size() == 2);
        test(s[0] == 5);
        test(s[1] == 15);

        s.erase(s.find(5));
        test(s.size() == 1);
        test(s[0] == 15);

        s.erase(s.find(15));
        test(s.size() == 0);
    }

    // erase(iterator) with std::greater
    {
        int data[] = {5, 10, 15, 20};
        SetG s(data, data + 4);

        s.erase(s.find(10));
        test(s.size() == 3);
        test(s[2] == 5);
        test(s[1] == 15);
        test(s[0] == 20);

        s.erase(s.find(20));
        test(s.size() == 2);
        test(s[1] == 5);
        test(s[0] == 15);

        s.erase(s.find(5));
        test(s.size() == 1);
        test(s[0] == 15);

        s.erase(s.find(15));
        test(s.size() == 0);
    }

    // erase(iterator, iterator)
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);

        s.erase(s.begin() + 1, s.begin() + 3);
        test(s.size() == 2);
        test(s[0] == 5);
        test(s[1] == 20);

        s.erase(s.begin() + 1, s.end());
        test(s.size() == 1);
        test(s[0] == 5);

        s.erase(s.begin(), s.end());
        test(s.size() == 0);
    }

    // erase(iterator, iterator) with std::greater
    {
        int data[] = {5, 10, 15, 20};
        SetG s(data, data + 4);

        s.erase(s.begin() + 1, s.begin() + 3);
        test(s.size() == 2);
        test(s[1] == 5);
        test(s[0] == 20);

        s.erase(s.begin() + 1, s.end());
        test(s.size() == 1);
        test(s[0] == 20);

        s.erase(s.begin(), s.end());
        test(s.size() == 0);
    }

    // clear
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);
        s.clear();
        test(s.size() == 0);
    }

    // clear with std::greater
    {
        int data[] = {5, 10, 15, 20};
        SetG s(data, data + 4);
        s.clear();
        test(s.size() == 0);
    }

    // key_comp, value_comp
    {
        Set s;
        test(s.key_comp()(1, 2));
        test(!s.key_comp()(2, 2));
        test(!s.key_comp()(2, 1));
        test(s.value_comp()(1, 2));
        test(!s.value_comp()(2, 2));
        test(!s.value_comp()(2, 1));

        SetG sg;
        test(!sg.key_comp()(1, 2));
        test(!sg.key_comp()(2, 2));
        test(sg.key_comp()(2, 1));
        test(!sg.value_comp()(1, 2));
        test(!sg.value_comp()(2, 2));
        test(sg.value_comp()(2, 1));
    }

    // count
    {
        Set s;
        test(s.count(0) == 0);

        s.insert(1);
        test(s.count(0) == 0);
        test(s.count(1) == 1);

        s.insert(1);
        test(s.count(0) == 0);
        test(s.count(1) == 1);

        s.insert(2);
        test(s.count(0) == 0);
        test(s.count(1) == 1);
        test(s.count(2) == 1);
    }

    // lower_bound, upper_bound, equal_range
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);

        test(s.lower_bound(10) == s.find(10));
        test(s.upper_bound(10) == s.find(15));
        test(s.lower_bound(9) == s.find(10));
        test(s.upper_bound(9) == s.find(10));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(10));
            test(p.second == s.find(10));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(15));
        }

        // the constant members functions are required by C++11 
        const Set& t = s; 
        test(t.lower_bound(10) == t.find(10));
        test(t.upper_bound(10) == t.find(15));
        test(t.lower_bound(9) == t.find(10));
        test(t.upper_bound(9) == t.find(10));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(10));
            test(p.second == s.find(10));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(15));
        }
    }

    // lower_bound, upper_bound, equal_range
    {
        int data[] = {5, 10, 15, 20};
        Set s(data, data + 4);

        test(s.lower_bound(10) == s.find(10));
        test(s.upper_bound(10) == s.find(15));
        test(s.lower_bound(9) == s.find(10));
        test(s.upper_bound(9) == s.find(10));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(10));
            test(p.second == s.find(10));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(15));
        }

        // the constant members functions are required by C++11 
        const Set& t = s; 
        test(t.lower_bound(10) == t.find(10));
        test(t.upper_bound(10) == t.find(15));
        test(t.lower_bound(9) == t.find(10));
        test(t.upper_bound(9) == t.find(10));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(10));
            test(p.second == s.find(10));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(15));
        }
    }

    // lower_bound, upper_bound, equal_range with std::greater
    {
        int data[] = {5, 10, 15, 20};
        SetG s(data, data + 4);

        test(s.lower_bound(10) == s.find(10));
        test(s.upper_bound(10) == s.find(5));
        test(s.lower_bound(9) == s.find(5));
        test(s.upper_bound(9) == s.find(5));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(5));
            test(p.second == s.find(5));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(5));
        }

        // the constant members functions are required by C++11 
        const SetG& t = s; 
        test(t.lower_bound(10) == t.find(10));
        test(t.upper_bound(10) == t.find(5));
        test(t.lower_bound(9) == t.find(5));
        test(t.upper_bound(9) == t.find(5));

        {
            std::pair<Iterator, Iterator> p = s.equal_range(6);
            test(p.first == s.find(5));
            test(p.second == s.find(5));

            p = s.equal_range(10);
            test(p.first == s.find(10));
            test(p.second == s.find(5));
        }
    }

    // get_allocator
    {
        Set s;
        Set::allocator_type allocator = s.get_allocator();
    }

    return 0;
}
