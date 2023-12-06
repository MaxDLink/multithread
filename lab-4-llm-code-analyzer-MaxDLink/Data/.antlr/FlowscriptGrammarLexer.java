// Generated from /Users/maxlink/Desktop/CS5393/lab-3-flowscript-interpreter-MaxDLink/Data/FlowscriptGrammar.g4.case1&2bak by ANTLR 4.13.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class FlowscriptGrammarLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, DIGRAPH=11, ID=12, STRING=13, WS=14;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "DIGRAPH", "ID", "STRING", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'{'", "'}'", "';'", "'['", "']'", "','", "'shape'", "'='", "'->'", 
			"'cluster_'", "'digraph'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, "DIGRAPH", 
			"ID", "STRING", "WS"
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


	public FlowscriptGrammarLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "FlowscriptGrammar.g4.case1&2bak"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u000e^\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0001\u0000\u0001\u0000\u0001"+
		"\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001"+
		"\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\u000b\u0001\u000b\u0005\u000bH\b\u000b\n\u000b\f\u000b"+
		"K\t\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0005\fQ\b\f\n\f\f\fT\t\f\u0001"+
		"\f\u0001\f\u0001\r\u0004\rY\b\r\u000b\r\f\rZ\u0001\r\u0001\r\u0000\u0000"+
		"\u000e\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004\t\u0005\u000b\u0006"+
		"\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017\f\u0019\r\u001b\u000e"+
		"\u0001\u0000\u0004\u0003\u0000AZ__az\u0004\u000009AZ__az\u0004\u0000\n"+
		"\n\r\r\"\"\\\\\u0003\u0000\t\n\r\r  a\u0000\u0001\u0001\u0000\u0000\u0000"+
		"\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000"+
		"\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000"+
		"\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f"+
		"\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013"+
		"\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017"+
		"\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b"+
		"\u0001\u0000\u0000\u0000\u0001\u001d\u0001\u0000\u0000\u0000\u0003\u001f"+
		"\u0001\u0000\u0000\u0000\u0005!\u0001\u0000\u0000\u0000\u0007#\u0001\u0000"+
		"\u0000\u0000\t%\u0001\u0000\u0000\u0000\u000b\'\u0001\u0000\u0000\u0000"+
		"\r)\u0001\u0000\u0000\u0000\u000f/\u0001\u0000\u0000\u0000\u00111\u0001"+
		"\u0000\u0000\u0000\u00134\u0001\u0000\u0000\u0000\u0015=\u0001\u0000\u0000"+
		"\u0000\u0017E\u0001\u0000\u0000\u0000\u0019L\u0001\u0000\u0000\u0000\u001b"+
		"X\u0001\u0000\u0000\u0000\u001d\u001e\u0005{\u0000\u0000\u001e\u0002\u0001"+
		"\u0000\u0000\u0000\u001f \u0005}\u0000\u0000 \u0004\u0001\u0000\u0000"+
		"\u0000!\"\u0005;\u0000\u0000\"\u0006\u0001\u0000\u0000\u0000#$\u0005["+
		"\u0000\u0000$\b\u0001\u0000\u0000\u0000%&\u0005]\u0000\u0000&\n\u0001"+
		"\u0000\u0000\u0000\'(\u0005,\u0000\u0000(\f\u0001\u0000\u0000\u0000)*"+
		"\u0005s\u0000\u0000*+\u0005h\u0000\u0000+,\u0005a\u0000\u0000,-\u0005"+
		"p\u0000\u0000-.\u0005e\u0000\u0000.\u000e\u0001\u0000\u0000\u0000/0\u0005"+
		"=\u0000\u00000\u0010\u0001\u0000\u0000\u000012\u0005-\u0000\u000023\u0005"+
		">\u0000\u00003\u0012\u0001\u0000\u0000\u000045\u0005c\u0000\u000056\u0005"+
		"l\u0000\u000067\u0005u\u0000\u000078\u0005s\u0000\u000089\u0005t\u0000"+
		"\u00009:\u0005e\u0000\u0000:;\u0005r\u0000\u0000;<\u0005_\u0000\u0000"+
		"<\u0014\u0001\u0000\u0000\u0000=>\u0005d\u0000\u0000>?\u0005i\u0000\u0000"+
		"?@\u0005g\u0000\u0000@A\u0005r\u0000\u0000AB\u0005a\u0000\u0000BC\u0005"+
		"p\u0000\u0000CD\u0005h\u0000\u0000D\u0016\u0001\u0000\u0000\u0000EI\u0007"+
		"\u0000\u0000\u0000FH\u0007\u0001\u0000\u0000GF\u0001\u0000\u0000\u0000"+
		"HK\u0001\u0000\u0000\u0000IG\u0001\u0000\u0000\u0000IJ\u0001\u0000\u0000"+
		"\u0000J\u0018\u0001\u0000\u0000\u0000KI\u0001\u0000\u0000\u0000LR\u0005"+
		"\"\u0000\u0000MQ\b\u0002\u0000\u0000NO\u0005\\\u0000\u0000OQ\t\u0000\u0000"+
		"\u0000PM\u0001\u0000\u0000\u0000PN\u0001\u0000\u0000\u0000QT\u0001\u0000"+
		"\u0000\u0000RP\u0001\u0000\u0000\u0000RS\u0001\u0000\u0000\u0000SU\u0001"+
		"\u0000\u0000\u0000TR\u0001\u0000\u0000\u0000UV\u0005\"\u0000\u0000V\u001a"+
		"\u0001\u0000\u0000\u0000WY\u0007\u0003\u0000\u0000XW\u0001\u0000\u0000"+
		"\u0000YZ\u0001\u0000\u0000\u0000ZX\u0001\u0000\u0000\u0000Z[\u0001\u0000"+
		"\u0000\u0000[\\\u0001\u0000\u0000\u0000\\]\u0006\r\u0000\u0000]\u001c"+
		"\u0001\u0000\u0000\u0000\u0005\u0000IPRZ\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}