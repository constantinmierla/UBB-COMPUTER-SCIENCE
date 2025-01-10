package service;

import java.util.Comparator;
import java.util.List;

import domain.GPSCoordinates;
import domain.ServiceProvider;
import repository.ServiceProviderRepository;

public class ServiceProviderServiceImpl implements ServiceProviderService {
	private DistanceCalculator distanceCalculator;
	private ServiceProviderRepository serviceProviderRepository;

	public ServiceProviderServiceImpl(DistanceCalculator distanceCalculator, ServiceProviderRepository repo) {
		this.distanceCalculator = distanceCalculator;
		this.serviceProviderRepository=repo;
	}

	@Override
	public ServiceProvider getNearestServiceProvider(GPSCoordinates customerBreakdown) {
		List<ServiceProvider>serviceProviders = serviceProviderRepository.getServiceProviders();
		
		serviceProviders.forEach(s->{
			Double distance = distanceCalculator.computeDistance(s.getCoordinates(), customerBreakdown);
			//TODO set computed distance for service provider
			s.setDistance(distance);
			
		});
		
		//TODO sort service providers based on distance descending
		serviceProviders.sort((s1, s2) ->s1.getDistance().compareTo(s2.getDistance()));
		return serviceProviders.get(0);
	}
}
