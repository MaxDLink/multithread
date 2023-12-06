// Generated from /Users/maxlink/Desktop/CS5393/lab-3-flowscript-interpreter-MaxDLink/Data/FlowscriptGrammar.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class FlowscriptGrammarParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, DIGRAPH=8, SUBGRAPH=9, 
		LABEL=10, ID=11, STRING=12, WS=13;
	public static final int
		RULE_flowscript = 0, RULE_graph_content = 1, RULE_subgraph = 2, RULE_subgraph_content = 3, 
		RULE_label_statement = 4, RULE_node_definition = 5, RULE_edge_definition = 6, 
		RULE_edge_label = 7;
	private static String[] makeRuleNames() {
		return new String[] {
			"flowscript", "graph_content", "subgraph", "subgraph_content", "label_statement", 
			"node_definition", "edge_definition", "edge_label"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{'", "'}'", "'='", "';'", "'['", "']'", "'->'", "'digraph'", 
			"'subgraph'", "'label'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, "DIGRAPH", "SUBGRAPH", 
			"LABEL", "ID", "STRING", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "FlowscriptGrammar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public FlowscriptGrammarParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FlowscriptContext extends ParserRuleContext {
		public TerminalNode DIGRAPH() { return getToken(FlowscriptGrammarParser.DIGRAPH, 0); }
		public TerminalNode ID() { return getToken(FlowscriptGrammarParser.ID, 0); }
		public Graph_contentContext graph_content() {
			return getRuleContext(Graph_contentContext.class,0);
		}
		public FlowscriptContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_flowscript; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterFlowscript(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitFlowscript(this);
		}
	}

	public final FlowscriptContext flowscript() throws RecognitionException {
		FlowscriptContext _localctx = new FlowscriptContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_flowscript);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(16);
			match(DIGRAPH);
			setState(17);
			match(ID);
			setState(18);
			match(T__0);
			setState(19);
			graph_content();
			setState(20);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Graph_contentContext extends ParserRuleContext {
		public List<SubgraphContext> subgraph() {
			return getRuleContexts(SubgraphContext.class);
		}
		public SubgraphContext subgraph(int i) {
			return getRuleContext(SubgraphContext.class,i);
		}
		public List<Node_definitionContext> node_definition() {
			return getRuleContexts(Node_definitionContext.class);
		}
		public Node_definitionContext node_definition(int i) {
			return getRuleContext(Node_definitionContext.class,i);
		}
		public List<Edge_definitionContext> edge_definition() {
			return getRuleContexts(Edge_definitionContext.class);
		}
		public Edge_definitionContext edge_definition(int i) {
			return getRuleContext(Edge_definitionContext.class,i);
		}
		public Graph_contentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_graph_content; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterGraph_content(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitGraph_content(this);
		}
	}

	public final Graph_contentContext graph_content() throws RecognitionException {
		Graph_contentContext _localctx = new Graph_contentContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_graph_content);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(27);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SUBGRAPH || _la==ID) {
				{
				setState(25);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
				case 1:
					{
					setState(22);
					subgraph();
					}
					break;
				case 2:
					{
					setState(23);
					node_definition();
					}
					break;
				case 3:
					{
					setState(24);
					edge_definition();
					}
					break;
				}
				}
				setState(29);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SubgraphContext extends ParserRuleContext {
		public TerminalNode SUBGRAPH() { return getToken(FlowscriptGrammarParser.SUBGRAPH, 0); }
		public TerminalNode ID() { return getToken(FlowscriptGrammarParser.ID, 0); }
		public Subgraph_contentContext subgraph_content() {
			return getRuleContext(Subgraph_contentContext.class,0);
		}
		public SubgraphContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subgraph; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterSubgraph(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitSubgraph(this);
		}
	}

	public final SubgraphContext subgraph() throws RecognitionException {
		SubgraphContext _localctx = new SubgraphContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_subgraph);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			match(SUBGRAPH);
			setState(31);
			match(ID);
			setState(32);
			match(T__0);
			setState(33);
			subgraph_content();
			setState(34);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Subgraph_contentContext extends ParserRuleContext {
		public List<Label_statementContext> label_statement() {
			return getRuleContexts(Label_statementContext.class);
		}
		public Label_statementContext label_statement(int i) {
			return getRuleContext(Label_statementContext.class,i);
		}
		public List<Node_definitionContext> node_definition() {
			return getRuleContexts(Node_definitionContext.class);
		}
		public Node_definitionContext node_definition(int i) {
			return getRuleContext(Node_definitionContext.class,i);
		}
		public Subgraph_contentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subgraph_content; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterSubgraph_content(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitSubgraph_content(this);
		}
	}

	public final Subgraph_contentContext subgraph_content() throws RecognitionException {
		Subgraph_contentContext _localctx = new Subgraph_contentContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_subgraph_content);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(40);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LABEL || _la==ID) {
				{
				setState(38);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case LABEL:
					{
					setState(36);
					label_statement();
					}
					break;
				case ID:
					{
					setState(37);
					node_definition();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(42);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Label_statementContext extends ParserRuleContext {
		public TerminalNode LABEL() { return getToken(FlowscriptGrammarParser.LABEL, 0); }
		public TerminalNode STRING() { return getToken(FlowscriptGrammarParser.STRING, 0); }
		public Label_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_label_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterLabel_statement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitLabel_statement(this);
		}
	}

	public final Label_statementContext label_statement() throws RecognitionException {
		Label_statementContext _localctx = new Label_statementContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_label_statement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			match(LABEL);
			setState(44);
			match(T__2);
			setState(45);
			match(STRING);
			setState(46);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Node_definitionContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(FlowscriptGrammarParser.ID, 0); }
		public TerminalNode LABEL() { return getToken(FlowscriptGrammarParser.LABEL, 0); }
		public TerminalNode STRING() { return getToken(FlowscriptGrammarParser.STRING, 0); }
		public Node_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_node_definition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterNode_definition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitNode_definition(this);
		}
	}

	public final Node_definitionContext node_definition() throws RecognitionException {
		Node_definitionContext _localctx = new Node_definitionContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_node_definition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(48);
			match(ID);
			setState(49);
			match(T__4);
			setState(50);
			match(LABEL);
			setState(51);
			match(T__2);
			setState(52);
			match(STRING);
			setState(53);
			match(T__5);
			setState(54);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Edge_definitionContext extends ParserRuleContext {
		public List<TerminalNode> ID() { return getTokens(FlowscriptGrammarParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(FlowscriptGrammarParser.ID, i);
		}
		public Edge_labelContext edge_label() {
			return getRuleContext(Edge_labelContext.class,0);
		}
		public Edge_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_edge_definition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterEdge_definition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitEdge_definition(this);
		}
	}

	public final Edge_definitionContext edge_definition() throws RecognitionException {
		Edge_definitionContext _localctx = new Edge_definitionContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_edge_definition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(56);
			match(ID);
			setState(57);
			match(T__6);
			setState(58);
			match(ID);
			setState(60);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__4) {
				{
				setState(59);
				edge_label();
				}
			}

			setState(62);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Edge_labelContext extends ParserRuleContext {
		public TerminalNode LABEL() { return getToken(FlowscriptGrammarParser.LABEL, 0); }
		public TerminalNode STRING() { return getToken(FlowscriptGrammarParser.STRING, 0); }
		public Edge_labelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_edge_label; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).enterEdge_label(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof FlowscriptGrammarListener ) ((FlowscriptGrammarListener)listener).exitEdge_label(this);
		}
	}

	public final Edge_labelContext edge_label() throws RecognitionException {
		Edge_labelContext _localctx = new Edge_labelContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_edge_label);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(64);
			match(T__4);
			setState(65);
			match(LABEL);
			setState(66);
			match(T__2);
			setState(67);
			match(STRING);
			setState(68);
			match(T__5);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\rG\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0005\u0001\u001a\b\u0001\n\u0001\f\u0001"+
		"\u001d\t\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0005\u0003\'\b\u0003\n\u0003\f\u0003"+
		"*\t\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0003\u0006=\b\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0000\u0000"+
		"\b\u0000\u0002\u0004\u0006\b\n\f\u000e\u0000\u0000D\u0000\u0010\u0001"+
		"\u0000\u0000\u0000\u0002\u001b\u0001\u0000\u0000\u0000\u0004\u001e\u0001"+
		"\u0000\u0000\u0000\u0006(\u0001\u0000\u0000\u0000\b+\u0001\u0000\u0000"+
		"\u0000\n0\u0001\u0000\u0000\u0000\f8\u0001\u0000\u0000\u0000\u000e@\u0001"+
		"\u0000\u0000\u0000\u0010\u0011\u0005\b\u0000\u0000\u0011\u0012\u0005\u000b"+
		"\u0000\u0000\u0012\u0013\u0005\u0001\u0000\u0000\u0013\u0014\u0003\u0002"+
		"\u0001\u0000\u0014\u0015\u0005\u0002\u0000\u0000\u0015\u0001\u0001\u0000"+
		"\u0000\u0000\u0016\u001a\u0003\u0004\u0002\u0000\u0017\u001a\u0003\n\u0005"+
		"\u0000\u0018\u001a\u0003\f\u0006\u0000\u0019\u0016\u0001\u0000\u0000\u0000"+
		"\u0019\u0017\u0001\u0000\u0000\u0000\u0019\u0018\u0001\u0000\u0000\u0000"+
		"\u001a\u001d\u0001\u0000\u0000\u0000\u001b\u0019\u0001\u0000\u0000\u0000"+
		"\u001b\u001c\u0001\u0000\u0000\u0000\u001c\u0003\u0001\u0000\u0000\u0000"+
		"\u001d\u001b\u0001\u0000\u0000\u0000\u001e\u001f\u0005\t\u0000\u0000\u001f"+
		" \u0005\u000b\u0000\u0000 !\u0005\u0001\u0000\u0000!\"\u0003\u0006\u0003"+
		"\u0000\"#\u0005\u0002\u0000\u0000#\u0005\u0001\u0000\u0000\u0000$\'\u0003"+
		"\b\u0004\u0000%\'\u0003\n\u0005\u0000&$\u0001\u0000\u0000\u0000&%\u0001"+
		"\u0000\u0000\u0000\'*\u0001\u0000\u0000\u0000(&\u0001\u0000\u0000\u0000"+
		"()\u0001\u0000\u0000\u0000)\u0007\u0001\u0000\u0000\u0000*(\u0001\u0000"+
		"\u0000\u0000+,\u0005\n\u0000\u0000,-\u0005\u0003\u0000\u0000-.\u0005\f"+
		"\u0000\u0000./\u0005\u0004\u0000\u0000/\t\u0001\u0000\u0000\u000001\u0005"+
		"\u000b\u0000\u000012\u0005\u0005\u0000\u000023\u0005\n\u0000\u000034\u0005"+
		"\u0003\u0000\u000045\u0005\f\u0000\u000056\u0005\u0006\u0000\u000067\u0005"+
		"\u0004\u0000\u00007\u000b\u0001\u0000\u0000\u000089\u0005\u000b\u0000"+
		"\u00009:\u0005\u0007\u0000\u0000:<\u0005\u000b\u0000\u0000;=\u0003\u000e"+
		"\u0007\u0000<;\u0001\u0000\u0000\u0000<=\u0001\u0000\u0000\u0000=>\u0001"+
		"\u0000\u0000\u0000>?\u0005\u0004\u0000\u0000?\r\u0001\u0000\u0000\u0000"+
		"@A\u0005\u0005\u0000\u0000AB\u0005\n\u0000\u0000BC\u0005\u0003\u0000\u0000"+
		"CD\u0005\f\u0000\u0000DE\u0005\u0006\u0000\u0000E\u000f\u0001\u0000\u0000"+
		"\u0000\u0005\u0019\u001b&(<";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}