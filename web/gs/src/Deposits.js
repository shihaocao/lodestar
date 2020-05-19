import React, { useState, useEffect, useRef} from 'react';
import Link from '@material-ui/core/Link';
import { makeStyles } from '@material-ui/core/styles';
import Typography from '@material-ui/core/Typography';
import Title from './Title';

function preventDefault(event) {
  event.preventDefault();
}

const useStyles = makeStyles({
  depositContext: {
    flex: 1,
  },
});

export default function Deposits(props) {
  const classes = useStyles();

  return (
    <React.Fragment>
      <Title>State</Title>
      <Typography component="p" variant="h4">
        CCNO: {props.ccno}
      </Typography>
      <Typography component="p" variant="h4">
        Mode: {props.mm_mode}
      </Typography>
      {/* <Typography color="textSecondary" className={classes.depositContext}>
        on 15 March, 2019
      </Typography> */}
    </React.Fragment>
  );
}
