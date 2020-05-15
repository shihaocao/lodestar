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

function preventDefault(event) {
  event.preventDefault();
}

const useStyles = makeStyles((theme) => ({
  seeMore: {
    marginTop: theme.spacing(3),
  },
}));

function array_to_table_cells(array, precision){
  return array.map((x) => (
  <TableCell>{x.toFixed(precision)}</TableCell>))
}

export default function Orders(props) {
  const classes = useStyles();

  let n = 10;
  let init_data = [];
  for(let i = 0; i<n; i++){
    init_data.push(inits.initial_point_from_cn(i+2*n))
  }

  // console.log(props.data);
  console.log(array_to_table_cells(props.data.quat))
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
  useEffect(() => update_data());

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
            <TableCell>&omega;<sub>x</sub></TableCell>
            <TableCell>&omega;<sub>y</sub></TableCell>
            <TableCell>&omega;<sub>z</sub></TableCell>

            <TableCell>q<sub>x</sub></TableCell>
            <TableCell>q<sub>y</sub></TableCell>
            <TableCell>q<sub>z</sub></TableCell>
            <TableCell>q<sub>w</sub></TableCell>
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
              {
                array_to_table_cells(row.gyr, 3)
              }
              {
                array_to_table_cells(row.quat, 3)
              }
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
