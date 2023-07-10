#ifndef MATRIX
#define MATRIX

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

#include "../../utils/includes/utils.h"

namespace s21{

template < class T >
class Matrix{
public:
    using value_type                = T;
    using row_matrix_type           = std::vector<value_type>;
    using matrix_type               = std::vector<row_matrix_type>;
    using size_type                 = typename matrix_type::size_type;
    using reference                 = typename matrix_type::reference;
    using const_reference           = typename matrix_type::const_reference;
    using iterator_type             = typename matrix_type::iterator;
    using const_iterator_type       = typename matrix_type::const_iterator;
    using reverse_iterator_type     = typename matrix_type::reverse_iterator;
    using reverse_const_iterator_type
                                = typename matrix_type::const_reverse_iterator;

    Matrix();
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) = default;
    Matrix(const matrix_type& inp_matrix);
    Matrix(matrix_type&& inp_matrix);
    ~Matrix() = default;

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    /**
     * @return value of the cell with [row][col] coordinates
     */
    value_type at(size_type row, size_type col);

    /**
     * @return value of the cell with [row][col] coordinates
     */
    value_type at(size_type row, size_type col) const;

    /**
     * @return the number of rows in Matrix
     */
    size_type RowsSize() const;

    /**
     * @return the number of columns in Matrix
     */
    size_type ColumnsSize() const;

    /**
     * @return iterator to the first row of Matrix
     */
    iterator_type Begin();

    /**
     * @return const iterator to the first row of Matrix
     */
    const_iterator_type Begin() const;

    /**
     * @return iterator to the element following the last Matrix's row
     */
    iterator_type End();

    /**
     * @return const iterator to the element following the last Matrix's row
     */
    const_iterator_type End() const;

    /**
     * @return reverse iterator to the beginning
     */
    reverse_iterator_type Rbegin();

    /**
     * @return const reverse iterator to the beginning
     */
    reverse_const_iterator_type Rbegin() const;

    /**
     * @return reverse iterator to the end
     */
    reverse_iterator_type Rend();

    /**
     * @return const reverse iterator to the end
     */
    reverse_const_iterator_type Rend() const;

    /**
     * Loading a matrix from a file [filename] in the adjacency matrix format
     * @return true if successful loading
     * @return false if not successful loading
     */
    bool LoadMatrixFromFile(std::string filename);

protected:
    matrix_type matrix_;
};

}

#include "../srcs/matrix.cc"

#endif
