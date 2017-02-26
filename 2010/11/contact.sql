-- phpMyAdmin SQL Dump
-- version 3.3.7
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 09, 2010 at 02:39 PM
-- Server version: 5.1.51
-- PHP Version: 5.3.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `reseller1`
--

-- --------------------------------------------------------

--
-- Table structure for table `contact`
--

CREATE TABLE IF NOT EXISTS `contact` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL COMMENT 'Numérico. Obligatorio. Todos los contactos han sido creados por un usuario del sistema. Éste es el ID de dicho usuario',
  `name` varchar(50) NOT NULL COMMENT 'Texto. Obligatorio. Nombre del contacto',
  `surname` varchar(50) NOT NULL COMMENT 'Texto. Obligatorio. Apellido del contacto',
  `country` varchar(50) NOT NULL COMMENT 'Texto. Obligatorio. Código del país del contacto. P.ej.: ES',
  `city` varchar(50) NOT NULL COMMENT 'Texto. Obligatorio. Ciudad donde reside el contacto',
  `province` varchar(50) NOT NULL COMMENT 'Texto. Obligatorio. Provincia donde reside el contacto',
  `address` varchar(255) NOT NULL COMMENT 'Texto. Obligatorio. Dirección del contacto',
  `address2` varchar(255) DEFAULT NULL COMMENT 'Texto. Opcional. Extensión de la dirección del contacto',
  `postal_code` varchar(5) NOT NULL COMMENT 'Texto. Obligatorio. Código postal de la dirección del contacto',
  `phone_prefix` int(11) NOT NULL COMMENT 'Numérico. Obligatorio. Prefijo para el número de teléfono. P.ej: 34',
  `phone_number` varchar(20) NOT NULL COMMENT 'Texto. Obligatorio. Número de teléfono del contacto',
  `fax_prefix` int(11) DEFAULT NULL COMMENT 'Numérico. Opcional. Prefijo para el número de fax. P.ej: 34',
  `fax_number` varchar(20) DEFAULT NULL COMMENT 'Texto. Opcional. Número de fax del contacto',
  `email` varchar(100) NOT NULL COMMENT 'Texto. Obligatorio. Dirección de correo electrónico del contacto',
  `company` varchar(40) DEFAULT NULL COMMENT 'Texto. Opcional. Empresa del contacto',
  PRIMARY KEY (`id`),
  KEY `user_id` (`user_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=17 ;

--
-- Dumping data for table `contact`
--

INSERT INTO `contact` (`id`, `user_id`, `name`, `surname`, `country`, `city`, `province`, `address`, `address2`, `postal_code`, `phone_prefix`, `phone_number`, `fax_prefix`, `fax_number`, `email`, `company`) VALUES
(7, 1, 'BadPhone', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'Calle de las Margaritas, 56', 'Juas', '28030', 34, '91', NULL, '', 'badphone@ramirez.net', 'UFO'),
(8, 1, 'NoFax', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'Calle de las Margarotas, 56', 'Try', '28030', 34, '918764987', NULL, '', 'nofax@ramirez.net', 'UFO'),
(9, 1, 'A', 'Short Name', 'ES', 'Madrid', 'Madrid', 'Calle de las Margarutas, 45', 'Hola', '28030', 34, '918767873', NULL, '918723485', 'shortname@shortname.com', 'UFO'),
(10, 1, 'ShortSurname', 'B', 'ES', 'Madrid', 'Madrid', 'Calle de las Margariutas, 87', 'Juas', '28030', 34, '918764859', NULL, '917632039', 'shortsurname@shortsurname.com', 'UFO'),
(11, 1, 'BadCity', 'Ramirez', 'ES', 'P', 'Madrid', 'Calle de las Supermargaritas, 87', 'Juas', '28030', 34, '918736478', NULL, '918738486', 'badcity@ramirez.net', 'UFO'),
(12, 1, 'BadProvince', 'Ramirez', 'ES', 'Madrid', 'P', 'Calle de las Margariitas, 87', 'Juas', '28030', 34, '918743987', NULL, '918749349', 'badprovince@ramirez.net', 'UFO'),
(13, 1, 'BadAddress', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'P', 'P', '28030', 34, '918763748', NULL, '918762383', 'badaddress@ramirez.net', 'UFO'),
(14, 1, 'BadCompany', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'Calle de las Margariotas, 98', 'Juas', '28030', 34, '918787656', NULL, '918798238', 'badcompany@ramirez.net', 'U'),
(15, 1, 'BadZip', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'Calle de las Margariuutas, 87', 'Juas', 'kk', 34, '918789876', NULL, '916728392', 'badzip@ramirez.net', 'UFO'),
(16, 1, 'BadEmail', 'Ramirez', 'ES', 'Madrid', 'Madrid', 'Calle de los Pristilos, 98', 'Juas', '28090', 34, '918783849', NULL, '918762373', 'bademailramirez.com', 'UFO');
