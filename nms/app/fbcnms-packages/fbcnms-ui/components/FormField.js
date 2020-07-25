/**
 * Copyright 2020 The Magma Authors.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @flow strict-local
 * @format
 */

import * as React from 'react';
import Text from './design-system/Text';

import {makeStyles} from '@material-ui/styles';

const useStyles = makeStyles(theme => ({
  root: {
    display: 'flex',
  },
  labelName: {
    color: theme.palette.grey.A700,
    fontWeight: 500,
    marginRight: '4px',
  },
  value: {
    textOverflow: 'ellipsis',
    overflowWrap: 'break-word',
    overflow: 'hidden',
  },
}));

type Props = {
  label: string,
  value?: ?React.Node,
};

export default function FormField(props: Props) {
  const classes = useStyles();
  const {label, value} = props;
  return (
    <div className={classes.root}>
      <Text className={classes.labelName} variant="body2">
        {label}:
      </Text>
      <Text className={classes.value} variant="body2">
        {value}
      </Text>
    </div>
  );
}
