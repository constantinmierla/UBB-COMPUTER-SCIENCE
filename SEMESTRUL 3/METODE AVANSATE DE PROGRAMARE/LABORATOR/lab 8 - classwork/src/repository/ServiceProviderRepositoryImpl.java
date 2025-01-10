package repository;

import domain.GPSCoordinates;
import domain.ServiceProvider;

import java.util.Arrays;
import java.util.List;

public class ServiceProviderRepositoryImpl implements ServiceProviderRepository {


    @Override
    public List<ServiceProvider> getServiceProviders() {
        ServiceProvider sp1 = new ServiceProvider("1934", "SP1", new GPSCoordinates(19.3, 435.2));
        ServiceProvider sp2 = new ServiceProvider("34232", "SP2", new GPSCoordinates(22.5, 9.3));
        ServiceProvider sp3= new ServiceProvider("2333","SP3",new GPSCoordinates(1.2, 0.4));

        return Arrays.asList(sp1, sp2, sp3);
    }
}
