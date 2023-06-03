<!DOCTYPE html>
<html>
    <?php 
        function handleLoginRequest() {
            if (isset($_POST["username"]) && isset($_POST["password"])) {
                header('Access-Control-Allow-Origin: *');
                $conn = new mysqli("localhost", "root", "", "university");
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                $username = $_POST["username"];
                $password = $_POST["password"];

                $query = "SELECT username, password FROM students WHERE username = ? AND password = ?;";
                $statement = $conn->prepare($query);
                $statement->bind_param("ss", $username, $password);
                $statement->execute();
                $statement->bind_result($username, $password);

                $noRows = 0;
                $loggedInStud;
                while ($statement->fetch()) {
                    $noRows++;
                    $loggedInStud = $username;
                }

                if ($noRows == 0) {
                    $query = "SELECT username, password FROM teachers WHERE username = ? AND password = ?;";
                    $statement = $conn->prepare($query);
                    $statement->bind_param("ss", $username, $password);
                    $statement->execute();
                    $statement->bind_result($username, $password);
                
                    $noRows = 0;
                    $loggedIn;
                    while ($statement->fetch()) {
                        $noRows++;
                        $loggedIn = $username;
                    }

                    if ($noRows == 0) {
                        echo "<p style='color: red'>Wrong username/password!</p>";
                    } else {
                        setcookie("logged-in", $loggedIn, time() + 600, "/");

                        echo "<form name='hiddenform' method='POST' action='teacher.php'>";
                        echo "<input type='hidden' name='u' id='u' value='$loggedIn'>";
                        echo "<script>document.hiddenform.submit();</script>";
                        echo "</form>";
                    }
                } else {
                    setcookie("logged-in", $loggedInStud, time() + 600, "/");

                    echo "<form name='hiddenform' method='POST' action='student.php'>";
                    echo "<input type='hidden' name='u' id='u' value='$loggedInStud'>";
                    echo "<script>document.hiddenform.submit();</script>";
                    echo "</form>";
                }

                $statement->close();
                $conn->close();
            }
        }
    ?>
    <head>
        <title>Problema 3</title>
        <style>
            .form-row {
                margin: 10px;
            }

        </style>
    </head>
    <body>
        <div id="form-div">
            <form action="login.php" method="POST">
                <div class="form-row">
                    <label for="username">Username</label>
                    <input type="text" id="username" name="username"><br>
                </div>

                <div class="form-row">
                    <label for="password">Password</label>
                    <input type="password" id="password" name="password"><br>
                </div>

                <div class = "form-row">
                    <input type="submit" value="Login">
                </div>
            </form>
        </div>
        <br>
        <div id="result">
            <?php
                handleLoginRequest();
            ?>
        </div>
    </body>
</html>
