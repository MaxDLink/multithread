// Generated from /Users/maxlink/Desktop/CS5393/lab-3-flowscript-interpreter-MaxDLink/Data/FlowscriptGrammar.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link FlowscriptGrammarParser}.
 */
public interface FlowscriptGrammarListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#flowscript}.
	 * @param ctx the parse tree
	 */
	void enterFlowscript(FlowscriptGrammarParser.FlowscriptContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#flowscript}.
	 * @param ctx the parse tree
	 */
	void exitFlowscript(FlowscriptGrammarParser.FlowscriptContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#graph_content}.
	 * @param ctx the parse tree
	 */
	void enterGraph_content(FlowscriptGrammarParser.Graph_contentContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#graph_content}.
	 * @param ctx the parse tree
	 */
	void exitGraph_content(FlowscriptGrammarParser.Graph_contentContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#subgraph}.
	 * @param ctx the parse tree
	 */
	void enterSubgraph(FlowscriptGrammarParser.SubgraphContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#subgraph}.
	 * @param ctx the parse tree
	 */
	void exitSubgraph(FlowscriptGrammarParser.SubgraphContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#subgraph_content}.
	 * @param ctx the parse tree
	 */
	void enterSubgraph_content(FlowscriptGrammarParser.Subgraph_contentContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#subgraph_content}.
	 * @param ctx the parse tree
	 */
	void exitSubgraph_content(FlowscriptGrammarParser.Subgraph_contentContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#label_statement}.
	 * @param ctx the parse tree
	 */
	void enterLabel_statement(FlowscriptGrammarParser.Label_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#label_statement}.
	 * @param ctx the parse tree
	 */
	void exitLabel_statement(FlowscriptGrammarParser.Label_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#node_definition}.
	 * @param ctx the parse tree
	 */
	void enterNode_definition(FlowscriptGrammarParser.Node_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#node_definition}.
	 * @param ctx the parse tree
	 */
	void exitNode_definition(FlowscriptGrammarParser.Node_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#edge_definition}.
	 * @param ctx the parse tree
	 */
	void enterEdge_definition(FlowscriptGrammarParser.Edge_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#edge_definition}.
	 * @param ctx the parse tree
	 */
	void exitEdge_definition(FlowscriptGrammarParser.Edge_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link FlowscriptGrammarParser#edge_label}.
	 * @param ctx the parse tree
	 */
	void enterEdge_label(FlowscriptGrammarParser.Edge_labelContext ctx);
	/**
	 * Exit a parse tree produced by {@link FlowscriptGrammarParser#edge_label}.
	 * @param ctx the parse tree
	 */
	void exitEdge_label(FlowscriptGrammarParser.Edge_labelContext ctx);
}