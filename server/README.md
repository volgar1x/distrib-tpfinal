distrib-tpfinal
===============

### Protocol

#### Create

_Create a bank account._

**Request:** `create,[name],[firstname]`

**Response:** `success,[id],[name],[firstname],[amount]`

#### Deposit

_Deposit money on the bank account._

**Request:** `deposit,[id],[amount]`

**Response:** `success,[id],[name],[firstname],[amount]`

**Error:** `error,amount_negative` _the server forbids every negative amount_

**Error:** `error,not_found` _if [id] references an unknown bank account_

#### Withdraw

_Withdraw money from the bank account._

**Request:** `withdraw,[id],[amount]`

**Response:** `success,[id],[name],[firstname],[amount]`

**Error:** `error,amount_negative` _the server forbids every negative amount_

**Error:** `error,not_found` _if [id] references an unknown bank account_

**Error:** `error,amount_too_high` _a bank account owner cannot withdraw more money than he currently has_

#### Query

_Query bank account's informations._

**Request:** `query,[id]`

**Response:** `success,[id],[name],[firstname],[amount]`

**Error:** `error,not_found` _if [id] references an unknown bank account_

#### Transfer

_Transfer money from a bank account to another._

**Request:** `transfer,[from_id],[to_id],[amount]`

**Response:** `success,[from_id],[from_name],[from_firstname],[from_amount]`

**Error:** `error,amount_negative` _the server forbids every negative amount_

**Error:** `error,amount_too_high` _a bank account owner cannot withdraw more money than he currently has_

**Error:** `error,not_found,from` *if [from_id] references an unknown bank account*

**Error:** `error,not_found,to` *if [to_id] references an unknown bank account*

#### Infos

_Update the informations of a bank account._

**Request **`infos,[id],[name],[firstname]`

**Response:** `success,[id],[name],[firstname],[amount]`

**Error:** `error,not_found` _if [id] references an unknown bank account_

