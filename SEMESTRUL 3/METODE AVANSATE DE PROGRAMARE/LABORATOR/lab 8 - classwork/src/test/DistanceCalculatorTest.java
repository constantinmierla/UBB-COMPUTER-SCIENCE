package test;

import org.junit.Before;
import org.junit.Test;

import domain.GPSCoordinates;
import service.DistanceCalculator;
import service.EuclideanDistanceCalculator;

import static org.junit.Assert.assertEquals;

public class DistanceCalculatorTest {
	
	private DistanceCalculator dist;
	
	@Before
	public void setUp(){
		dist=new EuclideanDistanceCalculator();
	}
	
	@Test
	public void testDistanceComputation(){
		GPSCoordinates point1=new GPSCoordinates(2.0, 3.0);
		GPSCoordinates point2=new GPSCoordinates(3.5, 2.5);
		
		//TODO add assertions for distance computation
		Double expectedDistance = Math.sqrt(Math.pow(2.0 - 3.5, 2) + Math.pow(3.0 - 2.5, 2));

		Double computedDistance = dist.computeDistance(point1, point2);

		assert(expectedDistance.equals(computedDistance));
	}

}
