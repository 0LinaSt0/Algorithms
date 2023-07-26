#ifndef __SLE_H__
#define __SLE_H__

#include <string>

#include "matrix.h"
#include "../../utils/includes/utils.h"
#include "../../utils/includes/exception.h"

namespace s21{

template< class T >
class Sle : public Matrix<T>{
public:
    template <typename Type>
    friend std::ostream& operator<<(
        std::ostream& out,
        const Sle<Type>& sle
    ){
        return out << dynamic_cast<const ::s21::Matrix<Type>&>(sle);
    }

    using parent_type       = Matrix<T>;
    using matrix_type       = typename parent_type::matrix_type;
    using size_type         = typename parent_type::size_type;
    using row_matrix_type   = typename parent_type::row_matrix_type;

    Sle() = delete;
    Sle(const Matrix<T>& inp_mtrx);
    Sle(Matrix<T>&& inp_mtrx);
    Sle(const Sle& other) = default;
    Sle(Sle&& other) = default;
    Sle(const matrix_type& inp_mtrx);
    Sle(matrix_type&& inp_mtrx);
    ~Sle() = default;

    Sle& operator=(const Sle& other);
    Sle& operator=(Sle&& other);

    /**
     * Load SLE from a file [filename] in the adjacency matrix format
     * @return new SLE<T> object
     * @throw SleException on invalid file
     */
    static Sle<T> LoadFromFile(const std::string& filename);

private:
    class SleException : public ::s21::Exception{
    public:
        SleException() = delete;
        SleException(const std::string& msg);
        SleException(SleException&&) = delete;
        ~SleException() = default;

        SleException& operator=(const SleException&) = delete;
        SleException& operator=(SleException&&) = delete;

        std::string GetMessage() const;
    };

    void ThrowOnInvalidInputMatrix_() const;

};

}

#include "../srcs/sle_impl.h"

#endif
