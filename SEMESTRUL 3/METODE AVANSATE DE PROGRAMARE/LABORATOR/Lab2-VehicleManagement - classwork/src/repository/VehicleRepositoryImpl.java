package repository;

import java.util.Calendar;

import domain.Vehicle;

public class VehicleRepositoryImpl implements VehicleRepository {
	private static final Integer MAX_CAPACITY = 100;

	private Vehicle[] vehicles;
	private int numberOfVehicles;

	public VehicleRepositoryImpl() {
		this.numberOfVehicles = 0;// there are no vehicles into the stock
		vehicles = new Vehicle[100];
	}

	public void addVehicle(Vehicle newVehicle) {
		//TODO add new condition, vehicle should not be inactive
		if (numberOfVehicles <= MAX_CAPACITY && !newVehicle.isInactive()) {
			vehicles[numberOfVehicles] = newVehicle;
			numberOfVehicles++;
		} else {
			System.out.println("No vehicles can be added to the stock");
		}
	}

	public Vehicle getVehicleAtPosition(int position) {
		return vehicles[position];
	}

	public int getNumberOfVehicles() {
		return numberOfVehicles;
	}

	public Vehicle[] getVehicles() {
		return vehicles;
	}

	@Override
	public void deleteVehicle(Vehicle vehicle) {
		Integer currentYear = Calendar.getInstance().get(Calendar.YEAR);

		if ((currentYear - vehicle.getYear()) > 30) {
			// we will delete the vehicle, mark it as being inactive
			vehicle.setInactive();
		}
	}
}
