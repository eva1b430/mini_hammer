#include "GraphNode.h"

GraphNode::GraphNode(void)
	: m_nIndex(em_Invalid_Node_Index)
	, m_vPosition(0.0f, 0.0f)
	, m_emType(0)
	, m_ExtraInfo(NULL)
{

}


GraphNode::~GraphNode(void)
{

}
