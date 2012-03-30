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

#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>

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
    boost::shared_ptr<std::vector<value_type> > storage_; 

    matrix_dimensions bounds_;  // Actual dimensions of the subject matrix.
    matrix_dimensions extents_; // Dimensions of this view.
    matrix_dimensions offsets_; // Offsets of this view.

    index_type indexer_;        // Indexing object.

  public:
    /// Constructs a new, empty matrix.
    local_matrix_view()
      : bounds_{0, 0}
      , extents_{0, 0}
      , offsets_{0, 0}
    {}

    /// Constructs a new matrix initialized from the matrix \a m.
    local_matrix_view(
        std::vector<std::vector<value_type> > const& m
        )
      : bounds_{0, 0}
      , extents_{0, 0}
      , offsets_{0, 0}
    {
        if (!m.empty() && !m[0].empty())
        {
            bounds_.rows = extents_.rows = m.size();
            bounds_.cols = extents_.cols = m[0].size();

            size_type const space = bounds_.rows * bounds_.cols;
            storage_.reset(new std::vector<value_type>(space));

            for (size_type i = 0; i < bounds_.rows; ++i)
            {
                BOOST_ASSERT(bounds_.cols == m[i].size());

                for (size_type j = 0; j < bounds_.cols; ++j)
                    (*this)(i, j) = m[i][j]; 
            }
        }
    }

    /// Constructs a new vector (n x 1 matrix) initialized from the vector \a v.
    local_matrix_view(
        std::vector<value_type> const& v
        )
      : bounds_{0, 0}
      , extents_{0, 0}
      , offsets_{0, 0}
    {
        if (!v.empty())
        {
            bounds_.rows = extents_.rows = v.size();
            bounds_.cols = extents_.cols = 1; 

            storage_.reset(new std::vector<value_type>(bounds_.rows));

            for (size_type i = 0; i < bounds_.rows; ++i)
                (*this)(i) = v[i];
        }
    }

    /// Construct a new matrix with dimensions \a rows x \a cols. Each element
    /// of the matrix is initialized to \a init.
    local_matrix_view(
        size_type rows
      , size_type cols = 1
      , value_type init = value_type()
        )
      : bounds_{rows, cols}
      , extents_{rows, cols}
      , offsets_{rows, cols}
    {
        if (rows && cols)
            storage_.reset(new std::vector<value_type>(rows * cols, init));
    } 

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
        )
      : storage_{other.storage_}
      , bounds_{other.bounds_}
      , extents_{other.extents_}
      , offsets_{other.offsets_}
    {}

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
      , matrix_dimensions extents
      , matrix_dimensions offsets = matrix_dimensions({0, 0}) 
        )
      : storage_{other.storage_}
      , bounds_{other.bounds_}
      , extents_{extents}
      , offsets_{offsets}
    {}

    // REVIEW: Is this correctly implemented?
    local_matrix_view(
        local_matrix_view&& other
        )
      : storage_{other.storage_}
      , bounds_{other.bounds_}
      , extents_{other.extents_}
      , offsets_{other.offsets_}
    {
        other.storage_.reset();
        other.bounds_ = matrix_dimensions({0, 0});
        other.extents_ = matrix_dimensions({0, 0});
        other.offsets_ = matrix_dimensions({0, 0});
    }

    local_matrix_view& operator=(
        std::vector<std::vector<value_type> > const& m
        )
    {
        if (!m.empty() && !m[0].empty())
        {
            offsets_.rows = offsets_.cols = 0;
            bounds_.rows = extents_.rows = m.size();
            bounds_.cols = extents_.cols = m[0].size();

            storage_.reset(
                new std::vector<value_type>(bounds_.rows * bounds_.cols));

            for (size_type i = 0; i < bounds_.rows; ++i)
            {
                BOOST_ASSERT(bounds_.cols == m[i].size());

                for (size_type j = 0; j < bounds_.cols; ++j)
                    (*this)(i, j) = m[i][j]; 
            }
        }

        else
        {
            storage_.reset();
            bounds_.rows = bounds_.cols = 0;
            extents_.rows = extents_.cols = 0;
            offsets_.rows = offsets_.cols = 0;
        }

        return *this;
    }

    local_matrix_view& operator=(
        std::vector<value_type> const& v
        )
    {
        if (!v.empty())
        {
            offsets_.rows = offsets_.cols = 0;
            bounds_.rows = extents_.rows = v.size();
            bounds_.cols = extents_.cols = 1; 

            storage_.reset(new std::vector<value_type>(bounds_.rows));

            for (size_type i = 0; i < bounds_.rows; ++i)
                (*this)(i) = v[i];
        }

        else
        {
            storage_.reset();
            bounds_.rows = bounds_.cols = 0;
            extents_.rows = extents_.cols = 0;
            offsets_.rows = offsets_.cols = 0;
        }

        return *this;
    }

    local_matrix_view& operator=(
        local_matrix_view const& other
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
        local_matrix_view&& other
        )
    {
        bounds_ = other.bounds_;
        extents_ = other.extents_;
        offsets_ = other.offsets_;
        storage_ = other.storage_;

        other.storage_.reset();
        other.bounds_ = matrix_dimensions({0, 0});
        other.extents_ = matrix_dimensions({0, 0});
        other.offsets_ = matrix_dimensions({0, 0});

        return *this;
    }

    reference operator()(
        size_type row
      , size_type col
        )
    {
        return (*storage_)[indexer_(row, col, bounds_, offsets_)];
    }

    reference operator()(
        size_type row
        )
    {
        BOOST_ASSERT(1 == extents_.cols);
        return (*storage_)[indexer_(row, 1, bounds_, offsets_)];
    }

    const_reference operator()(
        size_type row
      , size_type col
        ) const
    {
        return (*storage_)[indexer_(row, col, bounds_, offsets_)];
    }

    const_reference operator()(
        size_type row
        ) const
    {
        BOOST_ASSERT(1 == extents_.cols);
        return (*storage_)[indexer_(row, 1, bounds_, offsets_)];
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
        return storage_->data() + indexer_(0, 0, bounds_, offsets_);
    }

    const_pointer data() const
    {
        return storage_->data() + indexer_(0, 0, bounds_, offsets_);
    }
};

}

#endif // HPXLA_D0543949_3C98_4187_93A7_63F5C5B31EDE

