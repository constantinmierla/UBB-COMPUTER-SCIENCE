package test;

import org.junit.Before;
import org.junit.Test;

import repository.CustomerRepository;
import repository.CustomerRepositoryImpl;

public class CustomerRepositoryTest {
	
	private CustomerRepository customerRepository;

	@Before
	public void setUp(){
		this.customerRepository = new CustomerRepositoryImpl();
	}
	
	@Test
	public void testAddCustomer(){
		//TODO complete the test
	}
}
