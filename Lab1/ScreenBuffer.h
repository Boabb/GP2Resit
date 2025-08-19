#pragma once
#include <iostream>
#include <stdexcept>


static int noOfBufferSwaps = 0;

struct ScreenBuffer {
public:
    ScreenBuffer() {};

    ScreenBuffer(short x, short y) : row(x), col(y) {
        m_buffer = new char* [row];
        for (short i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }
    };

    ~ScreenBuffer() {
        if (m_buffer) {
            for (short i = 0; i < row; ++i) {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;
        }
    }

    ScreenBuffer(ScreenBuffer&& other) noexcept //Move Constructor
        : row(other.row), col(other.col), m_buffer(other.m_buffer)
    {
        // Reset the source object
        other.row = 0;
        other.col = 0;
        other.m_buffer = nullptr;
    }

    ScreenBuffer& operator=(ScreenBuffer&& other) noexcept //Move Assignment Operator
    {
        if (this != &other) {
            // Deallocate existing memory
            for (short i = 0; i < row; ++i) {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;

            // Transfer ownership
            row = other.row;
            col = other.col;
            m_buffer = other.m_buffer;

            // Reset the source object
            other.row = 0;
            other.col = 0;
            other.m_buffer = nullptr;

        }
        return *this;
    }

    //ScreenBuffer& operator<(Lane other) //Overloading < symbol to directly replace a ScreenBuffer row with the contents of a Lane
    //{
    //    if (!(other.lane != other.lane))
    //    {
    //        for (int i = 0; i < WIDTH; i++)
    //        {
    //            this->setChar(other.yPosition, i, other.lane[i]);
    //        }
    //    }
    //    return *this;
    //}

    ScreenBuffer(const ScreenBuffer& other) : row(other.row), col(other.col) //Copy Constructor 
    {
        // Allocate memory for m_buffer
        m_buffer = new char* [row];
        for (short i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }

        // Copy the data from other to this object
        for (short i = 0; i < row; ++i) {
            for (short j = 0; j < col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
    }

    ScreenBuffer& operator=(const ScreenBuffer& other) // Copy Assignment Operator
    {
        if (this == &other) {
            return *this;
        }

        // Deallocate existing memory
        for (short i = 0; i < row; ++i) {
                noOfBufferSwaps++;
                delete[] m_buffer[i];
        }
        delete[] m_buffer;

        // Allocate memory for new data
        row = other.row;
        col = other.col;
        m_buffer = new char* [row];
        for (short i = 0; i < row; ++i) {
            m_buffer[i] = new char[col];
        }

        // Copy the data from other to this object
        for (short i = 0; i < row; ++i) {
            for (short j = 0; j < col; ++j) {
                m_buffer[i][j] = other.m_buffer[i][j];
            }
        }
        return *this;
    }

    char& getChar(short row, short col) {
        validateIndices(row, col); // Ensure indices are within bounds
        return m_buffer[row][col];
    }

    void setChar(short row, short col, char value) {
        validateIndices(row, col); // Ensure indices are within bounds
        m_buffer[row][col] = value;
    }

    void validateIndices(short row, short col) const {
        if (row < 0 || row >= this->row || col < 0 || col >= this->col) {
            std::cerr << "Invalid indices: row=" << row << ", col=" << col 
                      << ", maxRow=" << this->row << ", maxCol=" << this->col << std::endl;
            throw std::out_of_range("Invalid indices.");
        }
    }


    bool trySetChar(short row, short col, char value)
    {
        if (this->getChar(row, col) == ' ')
        {
            this->setChar(row, col, value);
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    short row;
    short col;
    char** m_buffer;
};
