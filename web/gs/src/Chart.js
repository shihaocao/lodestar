import React, { useState, useEffect} from 'react';
import { useTheme } from '@material-ui/core/styles';
import { LineChart, Line, XAxis, YAxis, Label, ResponsiveContainer } from 'recharts';
import Title from './Title';

// Generate Sales Data
function createData(time, amount) {
  return { time, amount };
}

function createTelemData(ccno, altitude, lin_acc_z){
  return { ccno, altitude, lin_acc_z};
}

const data = [
  createData('00:00', 0),
  createData('03:00', 300),
  createData('06:00', 600),
  createData('09:00', 800),
  createData('12:00', 1500),
  createData('15:00', 2000),
  createData('18:00', 2400),
  createData('21:00', 2400),
  createData('24:00', undefined),
];

function interleave(times, vals){
  return times.reduce((acc, elem, i) => acc.concat(createData(elem, vals[i])),[]);
}

function interleave3(times, vals, v3){
  return times.reduce((acc, elem, i) => acc.concat(createTelemData(elem, vals[i], v3[i])),[]);
}

export default function Chart(props) {
  const theme = useTheme();

  const delta_alt = 1;
  console.log(props.data);

  return (
    <React.Fragment>
      <Title>Today</Title>
      <ResponsiveContainer>
        <LineChart
          data={props.data}
          margin={{
            top: 16,
            right: 16,
            bottom: 0,
            left: 24,
          }}
        >
          <XAxis dataKey="ccno" stroke={theme.palette.text.secondary} />
          <YAxis stroke={theme.palette.text.secondary}
                yAxisId="left"
                type="number" 
                domain={[dataMin => (Math.floor(dataMin)-delta_alt), max => (Math.floor(max)+delta_alt)]}>
            <Label
              angle={270}
              position="left"
              style={{ textAnchor: 'middle', fill: theme.palette.text.primary }}
            >
              Altitude (ASL) (m)
            </Label>
          </YAxis>
          <YAxis yAxisId="right" orientation="right" type="number"
                 domain={[-12,12]} allowDataOverflow={true}>
            <Label
              angle={90}
              position="right"
              style={{ textAnchor: 'middle', fill: theme.palette.text.primary }}
            >
              Linear Acceleration Z (g)
            </Label>
                 </YAxis>
          <Line yAxisId="left" type="monotone" dataKey="altitude" stroke={theme.palette.primary.main} dot={false} />
          <Line yAxisId="right" type="monotone" dataKey="lin_acc_z" stroke={theme.palette.primary.main} dot={false} />
        </LineChart>
      </ResponsiveContainer>
    </React.Fragment>
  );
}
