class Nulltype {};

// TypeList
template <typename ...Args>
struct TypeList
{
    using Head = Nulltype;
    using Tail = Nulltype;
};

template <typename H, typename ...T>
struct TypeList<H, T...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyTypeList;

template <typename H>
struct TypeList<H>
{
    using Head = H;
    using Tail = EmptyTypeList;
};


// TypeAt
template <int ind, typename ...T>
struct TypeAt
{
    using res = Nulltype;
};

template <int ind, typename ...T>
struct TypeAt<ind, TypeList<T...>>
{
    using res = typename TypeAt<ind - 1, typename TypeList<T...>::Tail>::res;
};

template <int ind>
struct TypeAt<ind, Nulltype>
{
    using res = Nulltype;
};

template <typename ...T>
struct TypeAt<0, TypeList<T...>>
{
    using res = typename TypeList<T...>::Head;
};


// A class that generates hierarchy
template <typename Type, typename TypeList, template<class> class Unit, int general_idx, int row_idx, int level_size, bool branching>
struct Generate;

// Nulltypes
template <typename TypeList, template<class> class Unit, int general_idx, int row_idx, int level_size>
struct Generate<Nulltype, TypeList, Unit, general_idx, row_idx, level_size, true> {};

template <typename TypeList, template<class> class Unit, int general_idx, int row_idx, int level_size>
struct Generate<Nulltype, TypeList, Unit, general_idx, row_idx, level_size, false> {};

// Non-branching
template <typename Type, typename TypeList, template<class> class Unit, int general_idx, int row_idx, int level_size>
struct Generate<Type, TypeList, Unit, general_idx, row_idx, level_size, false>
    : Generate<typename TypeAt<general_idx + level_size - 1, TypeList>::res, TypeList, Unit, general_idx + level_size, row_idx, level_size, true>
{
    using res = Generate<typename TypeAt<general_idx + level_size - 1, TypeList>::res, TypeList, Unit, general_idx + level_size, row_idx, level_size, true>;
};

// Branching
template <typename Type, typename TypeList, template<class> class Unit, int general_idx, int row_idx, int level_size>
struct Generate<Type, TypeList, Unit, general_idx, row_idx, level_size, true>
    : Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 2) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 2), 3 * row_idx - 2, 3 * level_size, false>,
      Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 1) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 1), 3 * row_idx - 1, 3 * level_size, false>,
      Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 0) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 0), 3 * row_idx - 0, 3 * level_size, false> 
{
    using l_res = Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 2) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 2), 3 * row_idx - 2, 3 * level_size, false>;
    using m_res = Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 1) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 1), 3 * row_idx - 1, 3 * level_size, false>;
    using r_res = Generate<typename TypeAt<general_idx + (level_size - row_idx) + (3 * row_idx - 0) - 1, TypeList>::res, TypeList, Unit, general_idx + (level_size - row_idx) + (3 * row_idx - 0), 3 * row_idx - 0, 3 * level_size, false>;
};

template <typename TypeList, template<class> class Unit>
struct GenCustomHierarchy
    : Generate<typename TypeAt<1 - 1, TypeList>::res, TypeList, Unit, 1, 1, 3, false>,
      Generate<typename TypeAt<2 - 1, TypeList>::res, TypeList, Unit, 2, 2, 3, false>,
      Generate<typename TypeAt<3 - 1, TypeList>::res, TypeList, Unit, 3, 3, 3, false>
{
    using l_res = Generate<typename TypeAt<1 - 1, TypeList>::res, TypeList, Unit, 1, 1, 3, false>;
    using m_res = Generate<typename TypeAt<2 - 1, TypeList>::res, TypeList, Unit, 2, 2, 3, false>;
    using r_res = Generate<typename TypeAt<3 - 1, TypeList>::res, TypeList, Unit, 3, 3, 3, false>;
};


template <typename T>
struct Holder {T obj;};

template <int n>
struct Node;

int main() {
    GenCustomHierarchy<TypeList<Node<1>, Node<2>, Node<3>, Node<4>, Node<5>, Node<6>, Node<7>, Node<8>, Node<9>, Node<10>, Node<11>, Node<12>, Node<13>, Node<14>, Node<15>, Node <16>, Node <17>, Node <18>>, Holder> a;
}
