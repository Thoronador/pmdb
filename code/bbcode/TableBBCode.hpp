/*
 -------------------------------------------------------------------------------
    This file is part of the Private Message Database.
    Copyright (C) 2012  Thoronador

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#ifndef BBCODE_TABLE_HPP
#define BBCODE_TABLE_HPP

#include "BBCode.hpp"
#include <map>

/** BBCode to handle table codes */
struct TableBBCode: public BBCode
{
  public:
    //constants for default class names used in constructor
    static const std::string DefaultTableClass;
    static const std::string DefaultRowClass;
    static const std::string DefaultCellClass;

    /** \brief constructor
     *
     * \param code             "name" of the code, i.e. "b" for [B]bold text[/B]
     * \param useGridClasses   if set to true, the generated HTML code will use
     *                         classes (as in CSS class) instead of a somewhat
     *                         bloated style attribute to generate the grids around
     *                         the table elements, if such the grids are required
     * \param tableClass       name of the class for grids on &lt;table&gt; tags
     * \param rowClass         name of the class for grids on &lt;tr&gt; tags
     * \param cellClass        name of the class for grids on &lt;td&gt; tags
     * \param tableWidthMax    the maximum width value (in pixels) that is allowed
     *                         in table attributes. Larger values will be ignored.
     *                         A value of zero means no limit.
     *
     * \remarks
     * If useGridClasses is set to false, the next three parameters do not
     * have any effect on the generated HTML code.
     */
    TableBBCode(const std::string& code, const bool useGridClasses=false,
                const std::string& tableClass=DefaultTableClass, const std::string& rowClass=DefaultRowClass,
                const std::string& cellClass=DefaultCellClass,
                const unsigned int tableWidthMax=0);

    /** \brief "applies" the BB code to the given text, i.e. transforms the BB code
     *         into its HTML representation
     *
     * \param text   the message text that (may) contain the BB code
     */
    virtual void applyToText(std::string& text) const;


    ///aux. structure
    struct OpeningElem
    {
      std::string::size_type open_pos, open_end;
      std::map<std::string, std::string> attributes;

      /** constructor */
      OpeningElem();

      /** \brief returns true, if the structure contains valid positions
       */
      virtual inline bool isValid() const
      {
        return ((open_pos!=std::string::npos) and (open_end!=std::string::npos));
      }
    }; //struct
  private:
    bool m_UseClasses; /**< whether or not to use the tree classes below */
    std::string m_TableClass; /**< class for use in table tags */
    std::string m_RowClass;   /**< class for use in tr tags */
    std::string m_CellClass;  /**< class for use in td tags */

    unsigned int m_TableWidthLimit; /**< max. width value (in px) allowed in tables */


    /** enumeration type for different elements of a table (table, row, cell) */
    enum TableElementType {tetTable, tetRow, tetCell};


    /** \brief appends style or class attributes (HTML) to the text
     *
     * \param text  the text to which the attributes shall be appended
     * \param eleType  type of element
     * \remarks Modifies the passed text directly.
     */
    void appendGridAttributes(std::string& text, const TableElementType eleType) const;


    /** \brief does the work that applyToText() is supposed to do in a recursive way
     *
     * \param text  the text message that may contain the BB code
     * \param offset offset at which processing should start
     * \return Returns true, if the text was processed completely without any errors.
     *         Returns false otherwise, i.e. when syntax errors are encountered.
     */
    bool actualApplyToText(std::string& text, const std::string::size_type offset) const;


    ///another aux. structure, this time for a complete table element
    struct TableElem: public OpeningElem
    {
      std::string::size_type end_pos; /**< end position of the table element */

      /** \brief returns true, if the structure contains valid positions
       */
      virtual inline bool isValid() const
      {
        return ((open_pos!=std::string::npos) and (open_end!=std::string::npos) and (end_pos!=std::string::npos));
      }
    }; //struct


    /** \brief gets the positions of the next opening element
     *
     * \param text    the text that will be searched
     * \param offset  offset at which the search begins
     * \param tag     the tag for which will be searched (e.g. "tr")
     * \return Returns an instance of OpeningElem with position values.
     */
    OpeningElem getNextOpeningElement(const std::string& text, const std::string::size_type offset, const std::string& tag) const;

    /** \brief splits the string of bb code attributes into a dictionary
     *
     * \param attr the string that contains the attributes, e.g. "align: center, width: 680, class: grid"
     * \return Returns a std::map where attribute name maps to attribute value.
     *         (Hooray for key-value-pairs.)
     */
    static std::map<std::string, std::string> explodeAttributes(std::string attr);


    /** \brief combines all given attributes to an HTML code string
     *
     * \param eleType  the type of the element
     * \param attrs    attributes of the element itself
     * \param parent_attrs  attributes of the element's parent element
     * \param grandparent_attrs  attributes of the element's parent element's parent element (i.e. "grandparent" element)
     * \return Returns the string that contains all HTML attributes for an element.
     */
    std::string attributesToString(const TableElementType eleType,
                                   const std::map<std::string, std::string>& attrs,
                                   const std::map<std::string, std::string>& parent_attrs = std::map<std::string, std::string>(),
                                   const std::map<std::string, std::string>& grandparent_attrs  = std::map<std::string, std::string>()) const;


    /** \brief returns true, if the passed attribute value contains an integer value
     *         that passes the table width limit
     *
     * \param attrValue   the attribute string (e.g. "650")
     */
    bool passesWidthLimit(const std::string& attrValue) const;
}; //struct

#endif // BBCODE_TABLE_HPP
