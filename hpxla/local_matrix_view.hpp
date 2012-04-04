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
#include <boost/make_shared.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>

namespace hpxla
{

// TODO: Container compatible.
template <
    typename T
  , typename Policy 
>
struct local_matrix_view
{
    template <
        typename T0
      , typename Policy0
    >
    friend struct local_matrix;

    typedef T value_type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef boost::uint64_t size_type;

    typedef Policy policy_type;
    typedef typename Policy::indexing_policy_type indexing_policy_type;
    typedef typename Policy::allocation_policy_type allocation_policy_type;

    typedef typename allocation_policy_type::template rebind<value_type>::other
        allocator_type;

  private:
    BOOST_COPYABLE_AND_MOVABLE(local_matrix_view);

    typedef std::vector<
        value_type
      , typename allocation_policy_type::template rebind<value_type>::other
    > storage_type;

    boost::shared_ptr<storage_type> storage_; 

    matrix_bounds bounds_;   // Actual dimensions of the subject matrix.
    matrix_bounds extents_;  // Dimensions of this view.
    matrix_offsets offsets_; // Offsets of this view.

    allocator_type alloc_;

    boost::shared_ptr<storage_type> create_storage(
        size_type size
      , const_reference init = value_type()
        )
    {
        // REVIEW: Use boost::move here?
        return boost::allocate_shared<storage_type>(alloc_, size, init);
    }

    boost::shared_ptr<storage_type> create_storage(
        storage_type const& s
        )
    {
        return boost::allocate_shared<storage_type>(alloc_, s);
    }

    boost::shared_ptr<storage_type> create_storage(
        BOOST_RV_REF(storage_type) s
        )
    {
        // REVIEW: Do I need to call boost::move here?
        return boost::allocate_shared<storage_type>(alloc_, boost::move(s));
    }

    friend class boost::serialization::access;

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template <
        typename Archive
    >
    void save(
        Archive& ar
      , unsigned version
        ) const 
    {
        ar & extents_;

        // REVIEW: Will the serialized data be smaller if we serialize this as
        // a contigous block of memory (e.g. array?).
        for (size_type i = 0; i < rows(); ++i)
            for (size_type j = 0; j < columns(); ++j)
                ar & (*this)(i, j); 
    }

    template <
        typename Archive
    >
    void load(
        Archive& ar
      , unsigned version
        )
    {
        ar & extents_;

        bounds_ = extents_;
        offsets_.rows = offsets_.cols = 0;

        storage_ = create_storage(bounds_.rows * bounds_.cols);

        for (size_type i = 0; i < rows(); ++i)
            for (size_type j = 0; j < columns(); ++j)
                ar & (*this)(i, j); 
    }

  public:
    /// Constructs a new, empty matrix.
    local_matrix_view(
        allocator_type const& alloc = allocator_type()
        )
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
      , alloc_(alloc)
    {}

#if defined(HPX_HAVE_CXX11_STD_INITIALIZER_LIST)
    /// Constructs a new matrix initialized from the matrix \a m.
    local_matrix_view(
        std::initializer_list<std::vector<value_type> > const& m
      , matrix_offsets offsets = matrix_offsets(0, 0)
      , allocator_type const& alloc = allocator_type()
        )
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
      , alloc_(alloc)
    {
        if (0 != m.size() && !(*m.begin()).empty())
        {
            bounds_.rows = extents_.rows = m.size();
            bounds_.cols = extents_.cols = (*m.begin()).size();

            storage_ = create_storage(bounds_.rows * bounds_.cols);

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

            offsets_ = offsets;
        }
    }

    /// Constructs a new vector (n x 1 matrix) initialized from the vector \a v.
    local_matrix_view(
        std::initializer_list<value_type> const& v
      , matrix_offsets offsets = matrix_offsets(0, 0)
      , allocator_type const& alloc = allocator_type()
        )
      : bounds_(0, 0)
      , extents_(0, 0)
      , offsets_(0, 0)
      , alloc_(alloc)
    {
        if (0 != v.size())
        {
            bounds_.rows = extents_.rows = v.size();
            bounds_.cols = extents_.cols = 1;

            storage_ = create_storage(bounds_.rows);

            typedef typename std::initializer_list<
                value_type
            >::const_iterator const_iterator; 

            const_iterator it = v.begin();

            for (size_type i = 0; i < bounds_.rows; ++i, ++it)
                (*this)(i) = *it; 

            offsets_ = offsets;
        }
    }
#endif

    /// Construct a new matrix with dimensions \a rows x \a cols. Each element
    /// of the matrix is initialized to \a init.
    local_matrix_view(
        size_type rows
      , size_type cols = 1
      , const_reference init = value_type()
      , matrix_offsets offsets = matrix_offsets(0, 0)
      , allocator_type const& alloc = allocator_type()
        )
      : bounds_(rows, cols)
      , extents_(rows, cols)
      , offsets_(offsets)
      , alloc_(alloc)
    {
        if (rows && cols)
            storage_ = create_storage(rows * cols, init);
    } 

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
        )
      : storage_(other.storage_)
      , bounds_(other.bounds_)
      , extents_(other.extents_)
      , offsets_(other.offsets_)
      , alloc_(other.alloc_)  
    {}

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
      , matrix_bounds extents
      , matrix_offsets offsets = matrix_offsets(0, 0) 
        )
      : storage_(other.storage_)
      , bounds_(other.bounds_)
      , extents_(extents)
      , offsets_(offsets)
      , alloc_(other.alloc_)  
    {}

    /// Construct a new view of the matrix pointed to by \a other.
    local_matrix_view(
        local_matrix_view const& other
      , matrix_offsets offsets 
        )
      : storage_(other.storage_)
      , bounds_(other.bounds_)
      , extents_(other.extents_)
      , offsets_(offsets)
      , alloc_(other.alloc_)  
    {}

    // REVIEW: Is this correctly implemented?
    local_matrix_view(
        BOOST_RV_REF(local_matrix_view) other
        )
      : storage_(boost::move(other.storage_))
      , bounds_(boost::move(other.bounds_))
      , extents_(boost::move(other.extents_))
      , offsets_(boost::move(other.offsets_))
      , alloc_(boost::move(other.alloc_)) 
    {
        other.storage_.reset();
        other.bounds_ = matrix_bounds(0, 0);
        other.extents_ = matrix_bounds(0, 0);
        other.offsets_ = matrix_offsets(0, 0);
        other.alloc_ = allocator_type();
    }

    local_matrix_view& operator=(
        BOOST_COPY_ASSIGN_REF(local_matrix_view) other
        )
    {
        bounds_ = other.bounds_;
        extents_ = other.extents_;
        offsets_ = other.offsets_;
        storage_ = other.storage_;
        alloc_ = other.alloc_;

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
        alloc_ = boost::move(other.alloc_);

        other.storage_.reset();
        other.bounds_ = matrix_bounds(0, 0);
        other.extents_ = matrix_bounds(0, 0);
        other.offsets_ = matrix_offsets(0, 0);
        other.alloc_ = allocator_type();

        return *this;
    }

    reference operator()(
        size_type row
      , size_type col
        )
    {
        size_type const i
            = indexing_policy_type::index(row, col, bounds_, offsets_);
        return (*storage_)[i];
    }

    reference operator()(
        size_type row
        )
    {
        BOOST_ASSERT(1 == extents_.cols);
        size_type const i
            = indexing_policy_type::index(row, 0, bounds_, offsets_);
        return (*storage_)[i];
    }

    const_reference operator()(
        size_type row
      , size_type col
        ) const
    {
        size_type const i
            = indexing_policy_type::index(row, col, bounds_, offsets_);
        return (*storage_)[i];
    }

    const_reference operator()(
        size_type row
        ) const
    {
        BOOST_ASSERT(1 == extents_.cols);
        size_type const i
            = indexing_policy_type::index(row, 0, bounds_, offsets_);
        return (*storage_)[i];
    }

    size_type rows() const
    {
        return extents_.rows;
    }

    size_type columns() const
    {
        return extents_.cols;
    }

    size_type size() const
    {
        return extents_.cols * extents_.rows;
    }

    bool empty() const
    {
        return !storage_;
    }

    pointer data()
    {
        return indexing_policy_type::compute_pointer
            (storage_->data(), bounds_, offsets_);
    }

    const_pointer data() const
    {
        return indexing_policy_type::compute_pointer
            (storage_->data(), bounds_, offsets_);
    }

    size_type vector_stride() const
    {
        return indexing_policy_type::vector_stride(bounds_);
    }

    size_type leading_dimension() const
    {
        return indexing_policy_type::leading_dimension(bounds_);
    }

    blas::index_order index_order() const
    {
        return indexing_policy_type::order();
    }
};

}

#endif // HPXLA_D0543949_3C98_4187_93A7_63F5C5B31EDE

