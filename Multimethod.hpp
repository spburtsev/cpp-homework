#ifndef UNTITLED_MULTIMETHOD_H
#define UNTITLED_MULTIMETHOD_H

#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>

using std::map;
using std::pair;
using std::type_index;
using std::function;

template<class Base, class Result, bool Commutative>
class Multimethod
{
    using Function = function<Result(Base*, Base*)>;

public:
    void addImpl(const type_index &t1, const type_index &t2, const Function &f)
    {
        methods_[{t1, t2}] = f;
    }

    bool hasImpl(Base* a, Base* b) const
    {
        if (!Commutative)
            return methods_.count({typeid(*a), typeid(*b)});

        bool result = methods_.count({typeid(*a), typeid(*b)})
                      || methods_.count({typeid(*b), typeid(*a)});
        return result;
    }

    Result call(Base* a, Base* b) const
    {
        if (methods_.count({typeid(*a), typeid(*b)}))
            return methods_.at({typeid(*a), typeid(*b)})(a, b);

        if (Commutative && methods_.count({typeid(*b), typeid(*a)}))
            return methods_.at({typeid(*b), typeid(*a)})(b, a);
    }

private:
    map<pair<type_index, type_index>, Function> methods_;
};

#endif