import java.util.ArrayList;

public class Stock {
    /**
	 * Here: all the needed class members and their getters and setters
	 */
	
	// All Class Members (Data)
	private String name;
	private String ticker;
	private String startDate;
	private int stockBrokers;
	private String description;
	private String exchangeCode;
	
	
	// Constructor
    public Stock(String name, String ticker, String startDate, int stockBrokers, String description, String exchangeCode) {
    	this.name = name;
    	this.ticker = ticker;
    	this.startDate = startDate;
    	this.stockBrokers = stockBrokers;
    	this.description = description;
    	this.exchangeCode = exchangeCode;
    }
    
    
    // Getters and Setters
    public void setName(String name) {
    	this.name = name;
    }
    
    public void setTicker(String ticker) {
    	this.ticker = ticker;
    }
    
    public void setStart(String start) {
    	this.startDate = start;
    }
    
    public void setBrokers(int brokers) {
    	this.stockBrokers = brokers;
    }
    
    public void setDescription(String description) {
    	this.description = description;
    }
  
    public void setExchange(String exchange) {
    	this.exchangeCode = exchange;
    }

    public String getName() {
    	return this.name;
    }
    
    public String getTicker() {
    	return this.ticker;
    }
    
    public String getStart() {
    	return this.startDate;
    }
    
    public int getBroker() {
    	return this.stockBrokers;
    }
    
    public String getDescription() {
    	return this.description;
    }
    
    public String getExchange() {
    	return this.exchangeCode;
    }
}

// Completed