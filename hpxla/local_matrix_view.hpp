////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPXLA_D0543949_3C98_4187_93A7_63F5C5B31EDE)
#define HPXLA_D0543949_3C98_4187_93A7_63F5C5B31EDE

#include <hpxla/local_fwd.hpp>

#include <vector>
#include <initializer_list>

#include <boost/assert.hpp>
#include <boost/move/move.hpp>
#include <boost/shared_ptr.hpp>

namespace hpxla
{

// TODO: Allocator support.
// TODO: Container compatible.
// TODO: LDA/stride stuff.
template <
    typename T
  , typename Index 
>
struct local_matrix_view
{
    template <
        typename T0
      , typename Index0
    >
    friend struct local_matrix;

    typedef T value_type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef std::size_t size_type;

    typedef Index index_type;

  private:
    BOOST_COPYABLE_AND_MOVEABLE(local_matrix);

    boost::shared_ptr<std::vector<value_type> > storage_; 

    matrix_dimensions bounds_;  // Actual dimensions of the subject matrix.
    matrix_dimensions extents_; // Dimensions of this view.
    matrix_dimensions offsets_; // Offsets of this view.

  public:
    /// Constructs a new, empty matrix.
    local_matrix_view()
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
    {}

#if defined(HPX_HAVE_CXX11_STD_INITIALIZER_LIST)
    /// Constructs a new matrix initialized from the matrix \a m.
    local_matrix_view(
        std::initializer_list<std::vector<value_type> > m
        )
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
    {
        if (0 != m.size() && !(*m.begin()).empty())
       {
            bounds_.rows = extents_.rows = m.size();
            bounds_.cols = extents_.cols = (*m.begin()).size();

            storage_.reset(
                new std::vector<value_type>(bounds_.rows * bounds_.cols));

            typedef typename std::initializer_list<
                std::vector<value_type>
            >::const_iterator const_iterator; 

            const_iterator it = m.begin();

            for (size_type i = 0; i < bounds_.rows; ++i, ++it)
            {
                BOOST_ASSERT(bounds_.cols == (*it).size());

                for (size_type j = 0; j < bounds_.cols; ++j)
                    (*this)(i, j) = (*it)[j]; 
            }
        }
    }

    /// Constructs a new vector (n x 1 matrix) initialized from the vector \a v.
    local_matrix_view(
        std::initializer_list<value_type> v
        )
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
    {
        if (0 != v.size())
        {
            bounds_.rows = extents_.rows = v.size();
            bounds_.cols = extents_.cols = 1;

            storage_.reset(new std::vector<value_type>(bounds_.rows));

            typedef typename std::initializer_list<
                value_type
            >::const_iterator const_iterator; 

            const_iterator it = v.begin();

            for (size_type i = 0; i < bounds_.rows; ++i, ++it)
                (*this)(i) = *it; 
        }
    }
#endif

    /// Construct a new matrix with dimensions \a rows x \a cols. Each element
    /// of the matrix is initialized to \a init.
    local_matrix_view(
        size_type rows
      , size_type cols = 1
      , value_type init = value_type()
        )
      : bounds_(rows, cols)
      , extents_(rows, cols)
      , offsets_(0, 0)
    {
        if (rows && cols)
            storage_.reset(new std::vector<value_type>(rows * cols, init));
    } 

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
        )
      : storage_(other.storage_)
      , bounds_(other.bounds_)
      , extents_(other.extents_)
      , offsets_(other.offsets_)
    {}

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
      , matrix_dimensions extents
      , matrix_dimensions offsets = matrix_dimensions(0, 0) 
        )
      : storage_(other.storage_)
      , bounds_(other.bounds_)
      , extents_(extents)
      , offsets_(offsets)
    {}

    // REVIEW: Is this correctly implemented?
    local_matrix_view(
        BOOST_RV_REF(local_matrix_view) other
        )
      : storage_(boost::move(other.storage_))
      , bounds_(boost::move(other.bounds_))
      , extents_(boost::move(other.extents_))
      , offsets_(boost::move(other.offsets_))
    {
        other.storage_.reset();
        other.bounds_ = matrix_dimensions(0, 0);
        other.extents_ = matrix_dimensions(0, 0);
        other.offsets_ = matrix_dimensions(0, 0);
    }

    local_matrix_view& operator=(
        BOOST_COPY_ASSIGN_REF(local_matrix_view) other
        )
    {
        bounds_ = other.bounds_;
        extents_ = other.extents_;
        offsets_ = other.offsets_;
        storage_ = other.storage_;

        return *this;
    }

    // REVIEW: Is this correctly implemented?
    local_matrix_view& operator=(
        BOOST_RV_REF(local_matrix_view) other
        )
    {
        storage_ = boost::move(other.storage_);
        bounds_ = boost::move(other.bounds_);
        extents_ = boost::move(other.extents_);
        offsets_ = boost::move(other.offsets_);

        other.storage_.reset();
        other.bounds_ = matrix_dimensions(0, 0);
        other.extents_ = matrix_dimensions(0, 0);
        other.offsets_ = matrix_dimensions(0, 0);

        return *this;
    }

    reference operator()(
        size_type row
      , size_type col
        )
    {
        return (*storage_)[index_type::index(row, col, bounds_, offsets_)];
    }

    reference operator()(
        size_type row
        )
    {
        BOOST_ASSERT(1 == extents_.cols);
        return (*storage_)[index_type::index(row, 0, bounds_, offsets_)];
    }

    const_reference operator()(
        size_type row
      , size_type col
        ) const
    {
        return (*storage_)[index_type::index(row, col, bounds_, offsets_)];
    }

    const_reference operator()(
        size_type row
        ) const
    {
        BOOST_ASSERT(1 == extents_.cols);
        return (*storage_)[index_type::index(row, 0, bounds_, offsets_)];
    }

    size_type rows() const
    {
        return extents_.rows;
    }

    size_type columns() const
    {
        return extents_.cols;
    }

    bool empty() const
    {
        return !storage_;
    }

    pointer data()
    {
        return index_type::compute_pointer(storage_->data(), bounds_, offsets_);
    }

    const_pointer data() const
    {
        return index_type::compute_pointer(storage_->data(), bounds_, offsets_);
    }

    size_type leading_dimension() const
    {
        return index_type::leading_dimension(bounds_);
    }

    blas::index_order index_order() const
    {
        return index_type::order();
    }
};

}

#endif // HPXLA_D0543949_3C98_4187_93A7_63F5C5B31EDE

