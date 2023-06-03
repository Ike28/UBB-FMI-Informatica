<!DOCTYPE html>
<html>
    <?php 
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

            if ($noRows != 0) {
                setcookie("logged-in-p6", $loggedInStud, time() + 600, "/");

                echo "<form name='hiddenform' method='POST' action='admin.php'>";
                echo "<input type='hidden' name='u' id='u' value='$loggedInStud'>";
                echo "<script>document.hiddenform.submit();</script>";
                echo "</form>";
            } else {
                echo "<p style='color: red;'>Wrong username/password!</p>";
            }
        }
    ?>
    <head>
        <title>Login Problema 6</title>
        <style>
            #username {
                margin-bottom: 10px;
            }

            #password {
                margin-bottom: 10px;
            }

        </style>
    </head>
    <body>
        <form action="login.php" method="POST"> 
            <div id="form-div">
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
            </div>
        </form>
    </body>
</html>
