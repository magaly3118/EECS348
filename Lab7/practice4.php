<!doctype html> 

<html>
    <head> 
        <meta charset="utf-8">
        <title>EECS 348 Lab 7 Practice 4</title>
        <link rel="stylesheet" type="text/css" href="sources/style.css"/>
    </head> 

    <body> 
        <div class='top'>
            <h1>EECS 348 LAB 7 Practice 4</h1>
        </div>

        <div class=bottom>
            <?php
                $num = intval($_POST['num']);
                echo "<p><strong>$num Multiplication Table</strong></p>";
            ?>

            <table border="1" class="bottom">
                <tr><th></th>
                <?php
                    $num = intval($_POST['num']);
                    
                    // header row with indexes
                    for ($i = 1; $i <= $num; $i++) {
                        echo "<th>$i</th>";
                    }

                    // rest of data
                    echo "</tr>";

                    for ($row = 1; $row <= $num; $row++) {
                        echo "<tr><th>$row</th>"; // header

                        // multiplication cells
                        for ($col = 1; $col <= $num; $col++) {
                            $res = $row * $col;
                            echo "<td>$res</td>";
                        }

                        echo "</tr>";
                    }
                ?>
            </table>
        </div><br>

        <button type="button" onclick="index()">Go to index</button>
        <button type="button" onclick="back()">Back to Practice 4</button>
    </body>

    <script>
        function index() { window.location.href = "index.html" };
        function back() { window.location.href = "practice4.html" };
    </script>
</html> 