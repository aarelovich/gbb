DROP TABLE IF EXISTS tStock;
DROP TABLE IF EXISTS tVentas;

-- Creating the unified patient data table
CREATE TABLE tStock (
    keyid              INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, 
    codigo             VARCHAR(255) UNIQUE,
	codigo_alt         VARCHAR(255),
    descripcion        VARCHAR(255),
    costo              FLOAT,
    costo_publico      FLOAT,
    costo_mayorista    FLOAT,
    stock_deposito     INT,
	stock_frente       INT,
	ubicacion          TEXT,
	columna            INT,
	estante            INT,
	marca              VARCHAR(255),
	tipo_producto      VARCHAR(255),
	envase             VARCHAR(255),
	minstock_deposito  INT,
	minstock_frente    INT,
);

CREATE TABLE tVentas (
    keyid              INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	producto           INT,
	fecha              DATETIME,
	pdf_factura         TEXT
);