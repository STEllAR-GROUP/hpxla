////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_DD44992F_CF37_4D24_BF44_3963793AEA5D)
#define HPXLA_DD44992F_CF37_4D24_BF44_3963793AEA5D

#include <hpxla/local_matrix_view.hpp>

namespace hpxla
{

// TODO: Allocator support.
// TODO: Container compatible.
// TODO: LDA/stride stuff.
template <
    typename T
  , typename Index 
>
struct local_matrix
{
    typedef local_matrix_view<T, Index> view_type;

    typedef typename view_type::value_type value_type;
    typedef typename view_type::reference reference;
    typedef typename view_type::const_reference const_reference;
    typedef typename view_type::pointer pointer;
    typedef typename view_type::const_pointer const_pointer;
    typedef typename view_type::size_type size_type;

    typedef typename view_type::index_type index_type;

  private:
    BOOST_COPYABLE_AND_MOVABLE(local_matrix);

    view_type view_;

  public:
    local_matrix() {}

#if defined(HPX_HAVE_CXX11_STD_INITIALIZER_LIST)
    local_matrix(
        std::initializer_list<std::vector<value_type> > m
        )
      : view_(m) 
    {}

    local_matrix(
        std::initializer_list<value_type> v
        )
      : view_(v) 
    {}
#endif

    local_matrix(
        size_type rows
      , size_type cols = 1
      , value_type init = value_type()
        )
      : view_(rows, cols, init) 
    {} 

    local_matrix(
        local_matrix const& other
        )
    {
        view_.bounds_ = other.view_.bounds_;
        view_.extents_ = other.view_.extents_;
        view_.offsets_ = other.view_.offsets_;

        if (  other.view_.bounds_.rows
           && other.view_.bounds_.cols
           && other.view_.storage_)
        {
            view_.storage_.reset(
                new std::vector<value_type>(*other.view_.storage_));
        }
    }

    // REVIEW: Is this correctly implemented?
    local_matrix(
        BOOST_RV_REF(local_matrix) other
        )
      : view_(boost::move(other.view_)) 
    {}

    local_matrix& operator=(
        BOOST_COPY_ASSIGN_REF(local_matrix) other
        )
    {
        view_.bounds_ = other.view_.bounds_;
        view_.extents_ = other.view_.extents_;
        view_.offsets_ = other.view_.offsets_;

        if (  other.view_.bounds_.rows
           && other.view_.bounds_.cols
           && other.view_.storage_)
        {
            view_.storage_.reset(
                new std::vector<value_type>(*other.view_.storage_));
        }

        else
            view_.storage_.reset();

        return *this;
    }

    // REVIEW: Is this correctly implemented?
    local_matrix& operator=(
        BOOST_RV_REF(local_matrix) other
        )
    {
        view_ = boost::move(other.view_);

        return *this;
    }

    reference operator()(
        size_type row
      , size_type col
        )
    {
        return view_(row, col);
    }

    reference operator()(
        size_type row
        )
    {
        return view_(row);
    }

    const_reference operator()(
        size_type row
      , size_type col
        ) const
    {
        return view_(row, col);
    }

    const_reference operator()(
        size_type row
        ) const
    {
        return view_(row);
    }

    size_type rows() const
    {
        return view_.rows();
    }

    size_type columns() const
    {
        return view_.columns();
    }

    bool empty() const
    {
        return view_.empty();
    }

    pointer data()
    {
        return view_.data();
    }

    const_pointer data() const
    {
        return view_.data();
    }

    size_type leading_dimension() const
    {
        return view_.leading_dimension();
    }

    blas::index_order index_order() const
    {
        return view_.index_order(); 
    }

    view_type& view()
    {
        return view_; 
    }

    view_type const& view() const
    {
        return view_;
    }
};

}

#endif // HPXLA_DD44992F_CF37_4D24_BF44_3963793AEA5D

