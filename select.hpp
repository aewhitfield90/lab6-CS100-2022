#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include "spreadsheet.hpp"

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

/* Select_Contains */
class Select_Contains : public Select_Column
{
protected:
    std::string searchStr;
public:
    Select_Contains(const Spreadsheet* sheet, const std::string& col, const std::string& name) : Select_Column(sheet, col), searchStr(name) {}
    
    virtual bool select(const std::string& s) const 
    {
        if (s.find(searchStr) != std::string::npos) { 
            return true;
        }
        else { return false; }
    }
};

/* Select_Not */
class Select_Not : public Select 
{
protected:
    Select* s;
public:
    Select_Not(Select* input) :s(input) {}
    ~Select_Not() { 
        delete s; 
    }

    virtual bool select(const Spreadsheet* sheet, int row) const 
    {
        return !s->select(sheet, row);
    }
};

/* Select_And */
class Select_And : public Select {
protected:
    Select* x;
    Select* y;
public:
    Select_And(Select* a, Select* b) :x(a), y(b) {}
    ~Select_And() { 
        delete x; 
        delete y; 
    }
    
    virtual bool select(const Spreadsheet* sheet, int row) const 
    {
        return (x->select(sheet, row) && y->select(sheet, row));
    }
};

/* Select_Or */
class Select_Or : public Select {
protected:
    Select* x;
    Select* y;
public:
    Select_Or(Select* a, Select* b) :x(a), y(b) {}
    ~Select_Or() {
        delete x;
        delete y;
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return (x->select(sheet, row) || y->select(sheet, row));
    }
};

#endif //__SELECT_HPP__
