<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json'); // Set the response content type to JSON

$con = new mysqli("localhost", "root", "", "news");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}


if (isset($_GET['filter_by_category'])) {
    $filterByCategory = $_GET['filter_by_category'];

    // prevent SQL injection
    $filterByCategory = mysqli_real_escape_string($con, $filterByCategory);

    $whereClause = '';

    if (!empty($filterByCategory)) {
        $whereClause .= "category LIKE '%$filterByCategory%'";
    } else {
        $whereClause .= "1"; // show all records
    }

    $sql = "SELECT * FROM news";

    if (!empty($whereClause)) {
        $sql .= " WHERE $whereClause";
    }
    else{
        echo json_encode(array('message' => 'No records found.'));
        $con->close();
        exit; // Stop further execution
    }

    // execute the query and fetch the results
    $result = $con->query($sql);

    $data=[];

    //$data = array();
    // while ($row = $result->fetch_assoc()) {
    //     $data[] = $row;
    // }


    if($result = mysqli_query($con, $sql))
    {
        $cr = 0;
        while($row = mysqli_fetch_assoc($result))
        {
            $data[$cr]['Text'] = $row['text'];
            $data[$cr]['Title'] = $row['title'];
            $data[$cr]['Producer'] = $row['producer'];
            $data[$cr]['Date'] = $row['date'];
            $data[$cr]['Category'] = $row['category'];
            $cr++;
  }
}

    if (!empty($data)) {
        echo json_encode($data);
    } else {
        echo json_encode(array('message' => 'No records found.'));
    }
}

$con->close();
?>
