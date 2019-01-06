@rem This script should be copied where the mysql_install.exe is (after downloading MariaDB Server)
@rem Change the path of the DB directory to the appropiate path

SET DBDIR="C:/Users/Viewmind/Documents/GBB/MYSQLDB/GBBDB"
mysql_install_db.exe --datadir=%DBDIR% --service=GBBDB --password=2019gbbdb --port=3306 -R 