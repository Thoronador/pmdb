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

#include "XMLNode.h"

XMLNode::XMLNode(const xmlNodePtr node)
{
  if (NULL==node)
    throw 42; //NULL not allowed
  m_Node = node;
}

const xmlChar* XMLNode::getName() const
{
  return m_Node->name;
}

std::string XMLNode::getNameAsString() const
{
  return reinterpret_cast<const char*>(m_Node->name);
}

XMLNode XMLNode::getChild() const
{
  return m_Node->children;
}

XMLNode XMLNode::getNextSibling() const
{
  return m_Node->next;
}

XMLNode XMLNode::getPrevSibling() const
{
  return m_Node->prev;
}

XMLNode XMLNode::getParent() const
{
  return m_Node->parent;
}

std::string XMLNode::getPlainTextContent() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be text node, of course
  if (m_Node->children->type!=XML_TEXT_NODE) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}

std::string XMLNode::getCDATAText() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be CTDA node, of course
  if (m_Node->children->type!=XML_CDATA_SECTION_NODE) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}

std::string XMLNode::getContentBoth() const
{
  //text is a child node of current node, so it has to have a child
  if (NULL==m_Node->children) return "";
  //type should be text or CDATA node
  if ((m_Node->children->type!=XML_TEXT_NODE) and (m_Node->children->type!=XML_CDATA_SECTION_NODE)) return "";
  xmlChar* key = xmlNodeListGetString(m_Node->doc, m_Node->children, 1);
  std::string result = reinterpret_cast<const char*>(key);
  xmlFree(key);//free it, because xmlNodeListGetString() allocated memory
  return result;
}
