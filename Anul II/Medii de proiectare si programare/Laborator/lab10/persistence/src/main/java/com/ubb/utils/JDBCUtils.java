package com.ubb.utils;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class JDBCUtils {
    private final Properties properties;
    private Connection connection = null;
    private static final Logger logger = LogManager.getLogger();

    public JDBCUtils(Properties properties) {
        this.properties = properties;
    }

    public Connection getConnection() {
        logger.traceEntry();
        try {
            if (connection == null) {
                connection = getNewConnection();
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(connection);
        return connection;
    }

    private Connection getNewConnection() throws SQLException {
        logger.traceEntry();

        String url = properties.getProperty("jdbc.url");
        String user = properties.getProperty("jdbc.user");
        String pass = properties.getProperty("jdbc.pass");

        logger.info("trying to connect to database ... {} ", url);
        logger.info("user: {} ", user);
        logger.info("pass: {} ", pass);
        Connection conn = null;
        try {
            if (user != null && pass != null)
                conn = DriverManager.getConnection(url,user,pass);
            else
                conn =DriverManager.getConnection(url);
        } catch (SQLException e) {
            logger.error(e);
            System.out.println("DB Error getting connection : " + e);
        }
        return conn;
    }
}
