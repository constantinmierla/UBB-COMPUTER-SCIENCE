package test;

import domain.Customer;
import domain.GPSCoordinates;
import domain.ServiceProvider;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;
import repository.CustomerRepository;
import repository.CustomerRepositoryImpl;
import repository.ServiceProviderRepository;
import repository.ServiceProviderRepositoryImpl;
import repository.VehicleRepository;
import repository.VehicleRepositoryImpl;
import service.CustomerService;
import service.CustomerServiceImpl;
import service.DistanceCalculator;
import service.EuclideanDistanceCalculator;
import service.ServiceProviderService;
import service.ServiceProviderServiceImpl;
import service.VehicleService;
import service.VehicleServiceImpl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.mockito.Mockito.*;


public class ServiceProviderServiceTest {

    private CustomerService customerService;
    private ServiceProviderService serviceProviderService;
    private VehicleService vehicleService;
    private CustomerRepository customerRepository;
    private VehicleRepository vehicleRepository;
    private ServiceProviderService realSPService;
    private DistanceCalculator distanceCalculator;
    private ServiceProviderRepository serviceProviderRepository;

    @Before
    public void setUp() {
    	serviceProviderRepository=new ServiceProviderRepositoryImpl();
    	distanceCalculator=new EuclideanDistanceCalculator();
        serviceProviderService = mock(ServiceProviderService.class);
        realSPService = new ServiceProviderServiceImpl(distanceCalculator, serviceProviderRepository);
        vehicleRepository = new VehicleRepositoryImpl();
        vehicleService = new VehicleServiceImpl(vehicleRepository);
        customerRepository = new CustomerRepositoryImpl();
        customerService = new CustomerServiceImpl(customerRepository, vehicleService, serviceProviderService);
    }

    @Test
    public void testBreakdownCase() {
        GPSCoordinates gpsCoordinates = new GPSCoordinates(2.14, 12.4);
        ServiceProvider nearest = new ServiceProvider("12", "Sam", new GPSCoordinates(4.5, 23.70));

        when(serviceProviderService.getNearestServiceProvider(gpsCoordinates)).thenReturn(nearest);
        Customer customer = new Customer("233", "John", 23, null, gpsCoordinates);

        customerService.breakdownScenario(customer);

        assertEquals(Boolean.TRUE, customer.isBreakdown());
    }

    @Test
    public void testNearestSP() {
        GPSCoordinates breakdownLocation = new GPSCoordinates(7.8, 2.12);

        ServiceProvider nearestProvider = new ServiceProvider(
                "SP1",
                "123-456-7890",
                new GPSCoordinates(7.9, 2.15)
        );

        ServiceProviderService realSPServiceMock = Mockito.mock(ServiceProviderService.class);
        Mockito.when(realSPServiceMock.getNearestServiceProvider(breakdownLocation)).thenReturn(nearestProvider);

        ServiceProvider sp = realSPServiceMock.getNearestServiceProvider(breakdownLocation);

        assertNotNull("The nearest service provider should not be null", sp);
        assertEquals("The returned service provider should be the nearest one", nearestProvider, sp);
    }
}
