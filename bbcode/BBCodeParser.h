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

#ifndef BBCODEPARSER_H
#define BBCODEPARSER_H

#include <string>
#include <vector>
#include "BBCode.h"
#include "Smilie.h"

/* class BBCodeParser:
       transforms a given text containing BB codes to HTML code via the
       parse() function. All codes that should be replaced have to be added
       before parsing. Use addCode() for that. Smilies added via addSmilie()
       will be replaced, too.
*/
class BBCodeParser
{
  public:
    /* transforms BB codes in text to HTML codes (still incomplete)

       parameters:
           text     - the original text
           forumURL - the base URL of the forum (some BB codes might require
                      this URL for proper transformation of code to HTML)
           isXHTML  - if set to true, smilie transformations will produce XHTML
                      image tags
    */
    std::string parse(std::string text, const std::string& forumURL, const bool isXHTML) const;

    /* adds a new bb code to the parser

       parameters:
           code - pointer to the BB code object that should be added

       remarks:
           The passed pointers must live for the whole lifetime of the
           BBCodeParser instance they are passed to. Otherwise parse() will
           fail. Alternatively call clearCodes() before you delete/free those
           BBCode objects.

           The parsing process during parse() calls will handle BBCodes in the
           order they are passed to addCode().

           Passing identical BBCode objects to this function without clearing
           old codes in between will not do any harm, it just causes this codes
           to be applied twice - although the second pass should not find any
           codes to replace, because the first one already took care of that.
    */
    void addCode(BBCode* code);

    /* adds a new smilie to the parser

       parameters:
           sm - the smilie
    */
    void addSmilie(const Smilie& sm);

    /* clears all added BB codes

       remarks:
           Clearing codes right before calling parse() without any addCode()
           calls in between will result in no BB codes being parsed. However,
           smilies might still get parsed.
    */
    void clearCodes();

    /* clears all added smilies

       remarks:
           Clearing smilies right before calling parse() without any addSmile()
           calls in between will result in no smilies being parsed. However,
           BB codes might still get parsed, if they are present.
    */
    void clearSmilies();
  private:
    std::vector<BBCode*> m_Codes;
    std::vector<Smilie>  m_Smilies;
};//class

#endif // BBCODEPARSER_H
