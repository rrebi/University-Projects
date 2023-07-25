<?php
include 'db.php';
session_start();

// Fetch parents and their child with matching attributes
$stmt = $conn->prepare("SELECT p.username, c.string, c.number, c.date
                       FROM parent p
                       INNER JOIN child c ON p.id = c.idP
                       WHERE (c.string, c.number, c.date) IN (
                           SELECT string, number, date
                           FROM child
                           GROUP BY string, number, date
                           HAVING COUNT(*) > 1
                       )");
$stmt->execute();
$result = $stmt->get_result();

// Store the retrieved data in an array
$parentChildData = array();
while ($row = $result->fetch_assoc()) {
    $parentChildData[] = $row;
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Parents with Same Child</title>
</head>
<body>
  <h1>Parents with Same Child</h1>

  <?php if (count($parentChildData) > 0) { ?>
    <table>
      <tr>
        <th>Parent Username</th>
        <th>Child String</th>
        <th>Child Number</th>
        <th>Child Date</th>
      </tr>
      <?php foreach ($parentChildData as $data) { ?>
        <tr>
          <td><?php echo $data['username']; ?></td>
          <td><?php echo $data['string']; ?></td>
          <td><?php echo $data['number']; ?></td>
          <td><?php echo $data['date']; ?></td>
        </tr>
      <?php } ?>
    </table>
  <?php } else { ?>
    <p>No parents with the same child found.</p>
  <?php } ?>
</body>
</html>
