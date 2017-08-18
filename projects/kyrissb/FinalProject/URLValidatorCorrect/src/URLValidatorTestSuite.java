import junit.framework.TestCase;


public class URLValidatorTestSuite extends TestCase {
	public int lineNum = 1;           // Add line numbering to tests
	public boolean outputAll = false; // Output all 68040 permutations when true (proof of concept)
	public boolean runFullURLTest = false; // Set to true to run the full URL test

	public URLValidatorTestSuite(String name) {
		super(name);
	}

	public void testURIComponent(String uri, boolean expected) {
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		if(outputAll){
			output(uri, expected, validator.isValid(uri));
		}
		else if(validator.isValid(uri) != expected) {
			output(uri, expected, validator.isValid(uri));
		}
		//assertEquals(validator.isValid(uri), expected);  // Comment out to keep the program from dying when an error is caught
	}
	
	public void output(String uri, boolean expected, boolean actual) {
		String resultMsg = lineNum + ") " + uri + " Actual validator result = " + actual + ", expected result = " + expected;
		System.out.println(resultMsg);
		lineNum++;
	}
	
	public void testURISchemes()
	{
		System.out.println("Schemes Test:");
		System.out.println();
		for(int i = 0; i < URISchemes.length; i++) {
			String uri = URISchemes[i].item + "www.google.com";
			testURIComponent(uri, URISchemes[i].valid);
		}
		System.out.println("--------------------------------------------------------------------------------");
	}
	
	public void testURIAuthorities()
	{
		System.out.println("Authorites Test:");
		System.out.println();
		for(int i = 0; i < URIAuthorities.length; i++) {
			String uri = "https://" + URIAuthorities[i].item;
			testURIComponent(uri, URIAuthorities[i].valid);
		}
		System.out.println("--------------------------------------------------------------------------------");
	}
	
	public void testURIPorts()
	{
		System.out.println("Ports Test:");
		System.out.println();
		for(int i = 0; i < URIPorts.length; i++) {
			String uri = "https://www.google.com" + URIPorts[i].item;
			testURIComponent(uri, URIPorts[i].valid);
		}
		System.out.println("--------------------------------------------------------------------------------");
	}
	
	public void testURIPaths()
	{
		System.out.println("Paths Test:");
		System.out.println();
		for(int i = 0; i < URIPaths.length; i++) {
			String uri = "https://www.google.com" + URIPaths[i].item;
			testURIComponent(uri, URIPaths[i].valid);
		}
		System.out.println("--------------------------------------------------------------------------------");
	}
	
	
	public void testURIQueries()
	{
		System.out.println("Queries Test:");
		System.out.println();
		for(int i = 0; i < URIQueries.length; i++) {
			String uri = "https://www.google.com" + URIQueries[i].item;
			testURIComponent(uri, URIQueries[i].valid);
		}
		System.out.println("--------------------------------------------------------------------------------");
	}
	
	// Hacky automated test that tests all  68040 permutations of URL components
	public void testFullURLs()
	{
		if(runFullURLTest){
			System.out.println("Full URL Test:");
			System.out.println();
			for(int scheme = 0; scheme < URISchemes.length; scheme++) {
				for(int auth = 0; auth < URIAuthorities.length; auth++){
					for(int port = 0; port < URIPorts.length; port++){
						for(int path = 0; path < URIPaths.length; path++){
							for(int query = 0; query < URIQueries.length; query++){
								String url = URISchemes[scheme].item 
										     + URIAuthorities[auth].item
										     + URIPorts[port].item
										     + URIPaths[path].item
										     + URIQueries[query].item;
								// Determine validity of URL from expected values
								boolean valid = false;
								if(URISchemes[scheme].valid &&
								   URIAuthorities[auth].valid &&
								   URIPorts[port].valid &&
								   URIPaths[path].valid &&
								   URIQueries[query].valid)
								{
									valid = true;
								}
								testURIComponent(url, valid);
							}
						}
					}
				}
			}
			System.out.println("--------------------------------------------------------------------------------");
		}
	}
	
	
	private ResultPair[] URISchemes = {
		new ResultPair("http://", true),
		new ResultPair("https://", true),
		new ResultPair("ftp://", true),
		new ResultPair("htt://", false),
		new ResultPair("http:", false),
		new ResultPair("http:/", false),
		new ResultPair("https/", false),
		new ResultPair("/", false),
		new ResultPair("", true),
	};
	
	private ResultPair[] URIAuthorities = {
		new ResultPair("www.google.com", true),
	    new ResultPair("amazon.com", true),
	    new ResultPair("uk.yahoo.com", true),
	    new ResultPair("www.yahoo.co.uk", true),
	    new ResultPair("yahoo.co.uk", true),
	    new ResultPair("0.0.0.0", true),
	    new ResultPair("192.168.0.1", true),
	    new ResultPair("223.com", true),
	    new ResultPair("www.ign.com", true),
	    new ResultPair("www.google.net", true),
	    new ResultPair("oregonstate.edu/", true),
	    new ResultPair("www.whitehouse.gov", true),
	    new ResultPair("www.amazon.9876", false),
	    new ResultPair("798.199.456.897", false),
	    new ResultPair("192.100.5.0.", false),
	    new ResultPair("192.160.2", false),
	    new ResultPair(".111.111.111.111", false),
	    new ResultPair("", false)
	};

	 private ResultPair[] URIPorts = {
	    new ResultPair(":0", true),
	    new ResultPair(":65535", true),
	    new ResultPair(":999", true),
	    new ResultPair(":1000", true),
		new ResultPair(":80", true),
		new ResultPair(":8080", true),
		new ResultPair(":808", true),
	    new ResultPair(":56432", true),
	    new ResultPair("", true),
	    new ResultPair(":23232", true),
	    new ResultPair(":65a", false),
	    new ResultPair(":-1", false),
	    new ResultPair(":-100", false),
	    new ResultPair(":$$$", false)
	 };
	 
	 private ResultPair[] URIPaths = {
		new ResultPair("/stuff/things/2", true),
	    new ResultPair("/stuff", true),
	    new ResultPair("/mail/", true),
	    new ResultPair("/$1000", true),
	    new ResultPair("", true),
	    new ResultPair("/", true),
	    new ResultPair("/..", false),
	    new ResultPair("/../", false),
	    new ResultPair("/..//words", false),
	    new ResultPair("/stuff//things//", false)
	 };
	 
	 private ResultPair[] URIQueries = {
		new ResultPair("", true),
	    new ResultPair("?gene=gaa&count=2345", true),
	    new ResultPair("?phenotype=spontaneousdentalhydroplosion", true),
	 };
}
