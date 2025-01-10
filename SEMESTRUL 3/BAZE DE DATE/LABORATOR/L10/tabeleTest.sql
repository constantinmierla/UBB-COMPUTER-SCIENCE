USE CFR;
GO

-- Tabel doar cu primary key --
CREATE TABLE TestPassengers (
    id_test_pas INT PRIMARY KEY IDENTITY, 
    name_test_pas VARCHAR(50) NOT NULL, 
    age INT CHECK(age > 0 AND age < 120),
    gender BIT NOT NULL                   -- 0 = Femeie, 1 = Barbat
);

-- Tabel cu primary key si foreign key --
CREATE TABLE TestDepartures (
    id_test_depart INT PRIMARY KEY IDENTITY,
    id_test_route INT NOT NULL FOREIGN KEY REFERENCES Routes(id_route),  -- referinta la Routes
    id_test_train INT NOT NULL FOREIGN KEY REFERENCES Trains(id_tr),     -- referinta la Trains
    departure_time DATETIME NOT NULL,
    price MONEY CHECK(price > 0)          -- validare pentru un pret pozitiv
);

-- Tabel cu primary key compus --
CREATE TABLE TestTickets (
    id_test_pas INT NOT NULL, -- legatura cu Passengers
    id_test_train INT NOT NULL,   -- legatura cu Trains
    PRIMARY KEY (id_test_pas, id_test_train)                           -- cheie primara compusa
);
