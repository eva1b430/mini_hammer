#include "GraphEdge.h"


GraphEdge::GraphEdge(void)
	: m_nFrom(GraphNode::em_Invalid_Node_Index)
	, m_nTo(GraphNode::em_Invalid_Node_Index)
	, m_fCost(1.0f)
{

}


GraphEdge::~GraphEdge(void)
{

}
