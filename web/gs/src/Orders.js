import React, { useState, useEffect} from 'react';
import Link from '@material-ui/core/Link';
import { makeStyles } from '@material-ui/core/styles';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Title from './Title';
var inits = require("./InitializeData");

// Generate Order Data
function createData(id, date, name, shipTo, paymentMethod, amount) {
  return { id, date, name, shipTo, paymentMethod, amount };
}

const rows = [
  createData(0, '16 Mar, 2019', 'Elvis Presley', 'Tupelo, MS', 'VISA ⠀•••• 3719', 312.44),
  createData(1, '16 Mar, 2019', 'Paul McCartney', 'London, UK', 'VISA ⠀•••• 2574', 866.99),
  createData(2, '16 Mar, 2019', 'Tom Scholz', 'Boston, MA', 'MC ⠀•••• 1253', 100.81),
  createData(3, '16 Mar, 2019', 'Michael Jackson', 'Gary, IN', 'AMEX ⠀•••• 2000', 654.39),
  createData(4, '15 Mar, 2019', 'Bruce Springsteen', 'Long Branch, NJ', 'VISA ⠀•••• 5919', 212.79),
];

function preventDefault(event) {
  event.preventDefault();
}

const useStyles = makeStyles((theme) => ({
  seeMore: {
    marginTop: theme.spacing(3),
  },
}));

export default function Orders(props) {
  const classes = useStyles();

  let n = 10;
  let init_data = [];
  for(let i = 0; i<n; i++){
    init_data.push(inits.initial_point_from_cn(i+2*n))
  }

  // console.log(props.data);
  console.log(init_data);
  const [local_data, set_data] = useState(init_data);

  const update_data = () => {
    let data_copy = local_data;
    // data_copy.shift();
    // let alts_copy = alts.co();
    // console.log(props.data)
    data_copy.unshift(props.data)
    data_copy.pop()
    set_data(data_copy);
    // console.log(local_data);
    // set_key(key + 1);
  }

  useEffect(() => {
    update_data();
  }, [update_data]);

  return (
    <React.Fragment>
      <Title>Telemetry Points</Title>
      <Table size="small">
        <TableHead>
          <TableRow>
            <TableCell>CCNO</TableCell>
            <TableCell>Altitude</TableCell>
            <TableCell>LinearAcc</TableCell>
            <TableCell>Acc</TableCell>
            <TableCell>Euler</TableCell>
            <TableCell>Gyr</TableCell>
            <TableCell>Quaternion</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {local_data.map((row) => (
            <TableRow key={row.ccno}>
              <TableCell>{row.ccno}</TableCell>
              <TableCell>{row.altitude}</TableCell>
              <TableCell>{row.linear_acc}</TableCell>
              <TableCell>{row.acc}</TableCell>
              <TableCell>{row.euler}</TableCell>
              <TableCell>{row.gyr}</TableCell>
              <TableCell>{row.quat}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
      <div className={classes.seeMore}>
        <Link color="primary" href="#" onClick={preventDefault}>
          See more orders
        </Link>
      </div>
    </React.Fragment>
  );
}
