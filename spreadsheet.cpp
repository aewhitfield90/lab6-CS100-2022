#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}

void Spreadsheet::print_selection(std::ostream& out) const
{
    /* if select points to null, prints everything */ 
    if (select == nullptr) {
        for (int i = 0; i < this->data.size(); i++) {   /* rows */ 

            for (int k = 0; k < this->column_names.size(); k++) {   /* columns */

                out << this->cell_data(i, k) << " ";
            } /* end of k for loop */ 
            
            out << std::endl;
        } /* end of i for loop */ 
    } /* end of if  */
    else {
        for (int i = 0; i < this->data.size(); i++) {   /* rows */ 

            if (this->select->select(this, i)) {    /* calls select function with row i */ 
                for (int k = 0; k < this->column_names.size(); k++) {   /* columns */
                    
                    out << this->cell_data(i, k) << " ";
                } /* end of k for loop */ 
                
                out << std::endl;
            } /* end of select() if */ 
        } /* end of i for loop */
    } /* end of else */ 
}
