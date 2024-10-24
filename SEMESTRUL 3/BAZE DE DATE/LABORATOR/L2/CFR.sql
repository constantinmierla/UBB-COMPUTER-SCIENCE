CREATE DATABASE CFR;
GO
USE CFR;
GO

CREATE TABLE Counties(
    id INT PRIMARY KEY IDENTITY,
    nameCo VARCHAR(50) NOT NULL
);

CREATE TABLE Cities(
    id INT PRIMARY KEY IDENTITY(1,1),
    nameCi VARCHAR(50) NOT NULL,
    county INT NOT NULL FOREIGN KEY REFERENCES Counties(id)
);

CREATE TABLE Streets(
    id INT PRIMARY KEY IDENTITY,
    nameS VARCHAR(50) NOT NULL,
    number INT NOT NULL,
    city INT NOT NULL FOREIGN KEY REFERENCES Cities(id)
);

CREATE TABLE Stations(
    id_st INT PRIMARY KEY IDENTITY,
    nameS VARCHAR(50) NOT NULL,
    id_address INT NOT NULL FOREIGN KEY REFERENCES Streets(id)
);

CREATE TABLE Trains(
    id_tr INT PRIMARY KEY IDENTITY,
    model VARCHAR(50) NOT NULL,
    capacity INT,
    registration VARCHAR(50) NOT NULL
);

CREATE TABLE Drivers(
    id_driver INT PRIMARY KEY IDENTITY,
    nameP VARCHAR(50) NOT NULL,
    birthdate DATETIME,
    height INT,
    weight INT,
    gender BIT NOT NULL,
    id_address INT NOT NULL FOREIGN KEY REFERENCES Streets(id),
    id_tr INT NOT NULL FOREIGN KEY REFERENCES Trains(id_tr)
);

CREATE TABLE AuxiliaryPer(
    id_per INT PRIMARY KEY IDENTITY,
    nameAP VARCHAR(50) NOT NULL,
    birthdate DATETIME,
    height INT,
    weight INT,
    gender BIT NOT NULL,
    id_address INT NOT NULL FOREIGN KEY REFERENCES Streets(id)
);

CREATE TABLE Passengers(
    id_pas INT PRIMARY KEY IDENTITY,
    nameP VARCHAR(50) NOT NULL,
    birthdate DATETIME NOT NULL,
    gender BIT NOT NULL,
    id_address INT NOT NULL FOREIGN KEY REFERENCES Streets(id)
);

CREATE TABLE Routes(
    id_route INT PRIMARY KEY IDENTITY,
    id_from INT NOT NULL FOREIGN KEY REFERENCES Stations(id_st),  
    id_to INT NOT NULL FOREIGN KEY REFERENCES Stations(id_st),    
    comfort_level INT,
    duration INT
);

CREATE TABLE Team(
    id_team INT PRIMARY KEY IDENTITY,
    id_driver INT NOT NULL FOREIGN KEY REFERENCES Drivers(id_driver),
    id_aux INT NOT NULL FOREIGN KEY REFERENCES AuxiliaryPer(id_per)
);

CREATE TABLE Departures(
    id_depart INT PRIMARY KEY IDENTITY,
    id_route INT NOT NULL FOREIGN KEY REFERENCES Routes(id_route),
    id_team INT NOT NULL FOREIGN KEY REFERENCES Team(id_team),
    fl_date DATETIME NOT NULL,
    price MONEY NOT NULL
);

CREATE TABLE Tickets(
    id_train INT NOT NULL FOREIGN KEY REFERENCES Trains(id_tr),
    id_pas INT NOT NULL FOREIGN KEY REFERENCES Passengers(id_pas),
    CONSTRAINT pk_Tickets PRIMARY KEY (id_train, id_pas)
);
